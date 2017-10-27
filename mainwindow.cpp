#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboSort->addItem("Sorting by SQL function");
    ui->comboSort->addItem("Sorting by standart ProxyModel function");
    ui->comboSort->addItem("Sorting by modified ProxyModel function");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
{
    model = new QSqlQueryModel(this);
    QString boxText = ui->comboBox->currentText();

    QTime timer;
    timer.start();

    if (boxText != "test")
        model->setQuery("SELECT * FROM " + boxText + ";");
    else
        model->setQuery("SELECT * FROM bookings.flights_v;");

    switch (ui->comboSort->currentIndex())
    {
        case 0:
        {
            connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
            ui->tableView->setModel(model);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        case 1:
        {
            QSortFilterProxyModel *stProxyModel = new QSortFilterProxyModel(this);
            stProxyModel->setSourceModel(model);
            ui->tableView->setModel(stProxyModel);
            qDebug() << "Построение и установка модели: " << timer.elapsed() << " ms";
            break;
        }

        case 2:
        {
            MySortFilterProxyModel *myProxyModel = new MySortFilterProxyModel(this);
            myProxyModel->setSourceModel(model);
            ui->tableView->setModel(myProxyModel);
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
    if (!query.exec("SELECT DISTINCT * FROM pg_tables WHERE tablename !~'^pg' AND tablename !~'^sql';"))
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

    if (ui->tableView->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder)
        model->setQuery("SELECT * FROM bookings.flights_v ORDER BY " + columnName + " ASC");
    else
        model->setQuery("SELECT * FROM bookings.flights_v ORDER BY " + columnName + " DESC");

    qDebug() << "Сортировка по столбцу" << model->headerData(column, Qt::Horizontal).toString() << "заняла: "
             << timer.elapsed() << " ms";
}



MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
{
}

MySortFilterProxyModel::~MySortFilterProxyModel()
{
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    QModelIndex newLeft = left;
    QModelIndex newRight = right;
    int count = 0;

    // проверяем не равны ли полученные данные и если равны, то переходим к сравнению по следующей колонке
    while (sourceModel()->data(newLeft) == sourceModel()->data(newRight))
    {
        if (count != sourceModel()->columnCount())
        {
            newLeft = left.sibling(left.row(),count);
            newRight = right.sibling(right.row(),count);
            count++;
        }
        else
            return true;
    }

    if (leftData.type() == QVariant::Int)
        return leftData.toInt() < rightData.toInt();

    if (leftData.type() == QVariant::String)
        return leftData.toString() < rightData.toString();

    if (leftData.type() == QVariant::DateTime)
        return leftData.toDateTime() < rightData.toDateTime();

    if (leftData.type() == QVariant::Date)
        return leftData.toDate() < rightData.toDate();

    if (leftData.type() == QVariant::Time)
        return leftData.toTime() < rightData.toTime();
}

void MySortFilterProxyModel::sort(int column, Qt::SortOrder order)
{
    QTime timer;
    timer.start();

    QSortFilterProxyModel::sort(column, order);

    qDebug() << "Сортировка по столбцу" << sourceModel()->headerData(column, Qt::Horizontal).toString() << "заняла: "
             << timer.elapsed() << " ms";
}
