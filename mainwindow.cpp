#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submitButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString boxText = ui->comboBox->currentText();

    QTime timer;
    timer.start();

    if (boxText != "test")
        model->setQuery("SELECT * FROM " + boxText + ";");
    else
        model->setQuery("SELECT * FROM bookings.flights_v;");

//    MySortFilterProxyModel *proxyModel = new MySortFilterProxyModel(model->columnCount(),this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);

    qDebug() << timer.elapsed() << " ms";
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

MySortFilterProxyModel::MySortFilterProxyModel(int columnCount, QObject *parent)
{
    for (int i = 0; i < columnCount; i++)
        actualColumns << i;
}

MySortFilterProxyModel::~MySortFilterProxyModel()
{
    delete &actualColumns;
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

//    const int tmp = left.column();
//    if (actualColumns.contains(left.column()))
//        actualColumns.removeAt(actualColumns.indexOf(tmp));
////        qDebug() << "true";
//    qDebug() << actualColumns;

    QMutableListIterator<int> it(actualColumns);
    while (it.hasNext())
    {
        int val = it.next();
        if (val == left.column())
            it.remove();
    }

    QModelIndex newLeft = index(left.row(),actualColumns[0]);
    QModelIndex newRight = index(right.row(),actualColumns[0]);

//    if (leftData == rightData) лучше переписать через такое

    if (leftData.type() == QVariant::Int)
    {
        if (leftData.toInt() == rightData.toInt())
            return lessThan(newLeft,newRight);
        else
            return leftData.toInt() < rightData.toInt();
    }

    if (leftData.type() == QVariant::String)
    {
        if (leftData.toString() == rightData.toString())
            return lessThan(newLeft,newRight);
        else
            return leftData.toString() < rightData.toString();
    }

    if (leftData.type() == QVariant::DateTime)
    {
        if (leftData.toDateTime() == rightData.toDateTime())
            return lessThan(newLeft,newRight);
        else
            return leftData.toDateTime() < rightData.toDateTime();
    }

    if (leftData.type() == QVariant::Date)
    {
        if (leftData.toDate() == rightData.toDate())
            return lessThan(newLeft,newRight);
        else
            return leftData.toDate() < rightData.toDate();
    }

    if (leftData.type() == QVariant::Time)
    {
        if (leftData.toTime() == rightData.toTime())
            return lessThan(newLeft,newRight);
        else
            return leftData.toTime() < rightData.toTime();
    }

    for (int i = 0; i < sourceModel()->columnCount(); i++)
        actualColumns << i;
}

void MySortFilterProxyModel::sort(int column, Qt::SortOrder order)
{
    QTime timer;
    timer.start();

    QSortFilterProxyModel::sort(column, order);

    qDebug() << timer.elapsed() << " ms";
}
