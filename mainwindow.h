#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QSortFilterProxyModel>
#include "dbconnection.h"

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    MySortFilterProxyModel(int columnCount, QObject *parent = 0);
    ~MySortFilterProxyModel();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    void sort(int column, Qt::SortOrder order);

private:
    mutable QList<int> actualColumns;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_submitButton_clicked();
    void on_actionAdd_Connection_triggered();
    void getOpenedDatabase(QSqlDatabase *m_db);

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    DBconnection *connection;
};

#endif // MAINWINDOW_H
