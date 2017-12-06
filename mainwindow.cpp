#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>

//static const int THREAD_COUNT = QThread::idealThreadCount();

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
    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
    connect(this, SIGNAL(sortChoiceChanged(MySortingMethods)), myProxyModel, SLOT(giveSortChoice(MySortingMethods)));

    // actionGroup in menu
    QActionGroup *actionGroup = new QActionGroup(ui->menuSortings);

    actionGroup->addAction(ui->actionQMap);
    actionGroup->addAction(ui->actionQuickSort);
    actionGroup->addAction(ui->actionHeapSort);
    actionGroup->addAction(ui->actionStableSort);
    actionGroup->addAction(ui->actionSimpleSort);
    actionGroup->addAction(ui->actionTimSort);
    actionGroup->setExclusive(true);
    sortChoice = QtMap;
    emit sortChoiceChanged(sortChoice);
    ui->menuSortings->addActions(actionGroup->actions());
}

MainWindow::~MainWindow()
{
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

    choice = static_cast<SortingMethods>(ui->comboSort->currentIndex());
    switch (choice)
    {
        case SQL:
            ui->tableView->setModel(model);
            break;

        case StandartModel:
            stProxyModel->setSourceModel(model);
            ui->tableView->setModel(stProxyModel);
            break;

        case MyModel:
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

    switch (choice)
    {
        case SQL:
            sortBySQL(column);
            qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                        ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
            break;

        case StandartModel:
            stProxyModel->sort(column, ui->tableView->horizontalHeader()->sortIndicatorOrder());
            qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                        ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
            break;

        case MyModel:
            myProxyModel->sort(column, ui->tableView->horizontalHeader()->sortIndicatorOrder());
            qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "в направлении" <<
                        ui->tableView->horizontalHeader()->sortIndicatorOrder() << "заняла: " << timer.elapsed() << "ms";
            break;

        default:
            break;
    }

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

void MainWindow::on_actionQMap_triggered()
{
    sortChoice = QtMap;
    emit sortChoiceChanged(sortChoice);
}

void MainWindow::on_actionQuickSort_triggered()
{
    sortChoice = QuickSort;
    emit sortChoiceChanged(sortChoice);
}

void MainWindow::on_actionHeapSort_triggered()
{
    sortChoice = HeapSort;
    emit sortChoiceChanged(sortChoice);
}

void MainWindow::on_actionStableSort_triggered()
{
    sortChoice = StableSort;
    emit sortChoiceChanged(sortChoice);
}

void MainWindow::on_actionSimpleSort_triggered()
{
    sortChoice = SimpleSort;
    emit sortChoiceChanged(sortChoice);
}

void MainWindow::on_actionTimSort_triggered()
{
    sortChoice = TimSort;
    emit sortChoiceChanged(sortChoice);
}
