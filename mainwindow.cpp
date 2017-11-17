#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>

//static const int THREAD_COUNT = QThread::idealThreadCount();
QTime sortingTimer;
int tmp = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hideFlag = true;
    ui->comboSort->addItem("Sorting by SQL function");
    ui->comboSort->addItem("Sorting by standart ProxyModel function");
    ui->comboSort->addItem("Sorting by modified ProxyModel function");

    model = new QSqlQueryModel(this);
    stProxyModel = new QSortFilterProxyModel(this);
    myProxyModel = new MySortFilterProxyModel(this);

    // connections
    connect(stProxyModel, SIGNAL(layoutChanged(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)), this, SLOT(on_stProxyModel_reset(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)));
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
}

MainWindow::~MainWindow()
{
//    delete model;
//    delete stProxyModel;
//    delete myProxyModel;
//    delete db;
//    delete connection;
    delete ui;
}

void MainWindow::sortBySQL(int column)
{
    QString columnName = model->record().fieldName(column);
    QString lastQueryText = model->query().lastQuery() + " ORDER BY ";
    QString queryText = lastQueryText.remove(lastQueryText.indexOf(" ORDER BY "),lastQueryText.length()-lastQueryText.indexOf(" ORDER BY "));

    model->setQuery(queryText + QString(" ORDER BY %1 %2").arg(columnName)
                    .arg(ui->tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder?"ASC":"DESC"));

}

void MainWindow::on_submitButton_clicked()
{
    QString boxText = ui->comboBox->currentText();

    QTime timer;
    timer.start();

    if (boxText != "test")
        model->setQuery("SELECT * FROM " + boxText);
    else
        model->setQuery("SELECT * FROM bookings.flights_v");

    choice = ui->comboSort->currentIndex();
    switch (choice)
    {
        case 0:
            ui->tableView->setModel(model);
            break;

        case 1:
            stProxyModel->setSourceModel(model);
            ui->tableView->setModel(stProxyModel);
            break;

        case 2:
            myProxyModel->setSourceModel(model);
            ui->tableView->setModel(myProxyModel);
            break;

        default:
            break;
    }

    qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
    ui->tableView->setSortingEnabled(true);
}

void MainWindow::on_actionAdd_Connection_triggered()
{
    connection = new DBconnection();
    connect(connection, SIGNAL(dbCorrectlyOpen(QSqlDatabase*)), this, SLOT(getOpenedDatabase(QSqlDatabase*)));

    if (connection)
    {
        connection->move(this->pos());
        connection->show();
    }
}

void MainWindow::getOpenedDatabase(QSqlDatabase *m_db)
{
    db = m_db;
    delete(connection);

    QSqlQuery query = QSqlQuery(*db);
    if (!query.exec("SELECT DISTINCT * FROM pg_tables WHERE tablename !~'^pg' AND tablename !~'^sql'"))
    {
        QMessageBox::warning(this, tr("Error"), tr("An error occurred while "
                                   "trying to execute a database query: ") + query.lastError().text());
    }
    else
    {
        QStringList TablesList = QStringList();

        TablesList.append("test");
        while (query.next())
        {
            QString name = query.value(0).toString() + '.' + query.value(1).toString();
            qDebug() << name;
            TablesList.append(name);
        }
        ui->comboBox->addItems(TablesList);
    }
}

void MainWindow::on_sectionClicked(int column)
{  
    QTime timer;
    timer.start();
    sortingTimer.restart();

    switch (choice)
    {
        case 0:
            sortBySQL(column);
            qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                        ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
            break;

        case 1:
            stProxyModel->sort(column, ui->tableView->horizontalHeader()->sortIndicatorOrder());
            break;

        case 2:
            myProxyModel->sort(column, ui->tableView->horizontalHeader()->sortIndicatorOrder());
            qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                        ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
            break;

        default:
            break;
    }

    ui->tableView->reset();
    ui->tableView->verticalHeader()->reset();
}

void MainWindow::on_actionHide_vertical_headers_triggered()
{
    hideFlag = !hideFlag;
    ui->tableView->verticalHeader()->setHidden(hideFlag);
}

void MainWindow::on_revertButton_clicked()
{
    model->clear();
    ui->tableView->setModel(NULL);
}

void MainWindow::on_stProxyModel_reset(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)
{
    // как-то надо это подогнать под свою задачу (засечь время для стандартной модели)
    qDebug() << "Сортировка" << "в направлении" << ui->tableView->horizontalHeader()->sortIndicatorOrder()
             << "заняла: " << sortingTimer.elapsed() << "ms";
}
