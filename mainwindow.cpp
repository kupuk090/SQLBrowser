#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>

static const int THREAD_COUNT = QThread::idealThreadCount();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboSort->addItem("Sorting by SQL function");
    ui->comboSort->addItem("Sorting by standart ProxyModel function");
    ui->comboSort->addItem("Sorting by modified ProxyModel function");
    ui->comboSort->addItem("Sorting by standart Model function");

    model = new QSqlQueryModel();
//    modelThread = new QThread(this);
//    connect(this, SIGNAL(destroyed()), modelThread, SLOT(quit()));
//    model->moveToThread(modelThread);

    myProxyModel = new MySortFilterProxyModel(this);
    connect(this, SIGNAL(modelChanged()), myProxyModel, SLOT(revertList()));
}

MainWindow::~MainWindow()
{
    delete ui;
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

    switch (ui->comboSort->currentIndex())
    {
        case 0:
        {
            disconnect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            ui->tableView->setModel(model);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        case 1:
        {
            QSortFilterProxyModel *stProxyModel = new QSortFilterProxyModel(this);
            disconnect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            stProxyModel->setSourceModel(model);
            ui->tableView->setModel(stProxyModel);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        case 2:
        {
//            MySortFilterProxyModel *myProxyModel = new MySortFilterProxyModel(this);
            disconnect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            myProxyModel->setSourceModel(model);
            ui->tableView->setModel(myProxyModel);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        case 3:
        {
            disconnect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            disconnect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(modelSorting(int)));
            connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(modelSorting(int)));
            ui->tableView->setModel(model);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        default:
            break;
    }

    ui->tableView->setSortingEnabled(true);
}

void MainWindow::on_actionAdd_Connection_triggered()
{
    connection = new DBconnection();

    connect(connection, SIGNAL(dbCorrectlyOpen(QSqlDatabase*)), this, SLOT(getOpenedDatabase(QSqlDatabase*)));
    connection->show();
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

    QString columnName = model->record().fieldName(column);
    QString lastQueryText = model->query().lastQuery() + " ORDER BY ";
    QString queryText = lastQueryText.remove(lastQueryText.indexOf(" ORDER BY "),lastQueryText.length()-lastQueryText.indexOf(" ORDER BY "));

//    if (ui->tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder)
//        model->setQuery(queryText + " ORDER BY " + columnName + " ASC");
//    else
//        model->setQuery(queryText + " ORDER BY " + columnName + " DESC");

    model->setQuery(queryText + QString(" ORDER BY %1 %2").arg(columnName)
                    .arg(ui->tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder?"ASC":"DESC"));

    //qDebug() << model->lastError().text();

    qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
}

void MainWindow::modelSorting(int column)
{
    QTime timer;
    timer.start();

    // в QSqlQueryModel стандартной функции сортировки не имеется, зато она имеется в QSqlTableModel
    // но в нём, похоже она реализована в виде SQL-запросов к бд
    //model->sort(column, ui->tableView->horizontalHeader()->sortIndicatorOrder());

    qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
}
