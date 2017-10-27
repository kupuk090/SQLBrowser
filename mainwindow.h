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
    MySortFilterProxyModel(QObject *parent = 0);
    ~MySortFilterProxyModel();

//    void sortFromSql(QSqlQueryModel *model);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    void sort(int column, Qt::SortOrder order);
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
    void on_sectionClicked(int column);

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    DBconnection *connection;
    QSqlQueryModel *model;
};

#endif // MAINWINDOW_H
