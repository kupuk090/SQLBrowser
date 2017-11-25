#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QSortFilterProxyModel>
#include "mysortfilterproxymodel.h"
#include "dbconnection.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sortBySQL(int column);

private slots:
    void on_submitButton_clicked();
    void on_actionAdd_Connection_triggered();
    void getOpenedDatabase(QSqlDatabase *m_db);
    void on_sectionClicked(int column);
    void on_actionHide_vertical_headers_triggered();
    void on_revertButton_clicked();
    void on_stProxyModel_reset();

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    DBconnection *connection;
    QSqlQueryModel *model;
    QSortFilterProxyModel *stProxyModel;
    MySortFilterProxyModel *myProxyModel;
    int choice;     // 0 - for SQL sorting, 1 - for QSortFilterProxyModel::sort(...), 2 - for modified sorting of proxy-model
    bool hideFlag;

signals:
    void modelChanged();
};

#endif // MAINWINDOW_H
