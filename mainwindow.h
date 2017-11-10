#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QThread>
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

private slots:
    void on_submitButton_clicked();
    void on_actionAdd_Connection_triggered();
    void getOpenedDatabase(QSqlDatabase *m_db);
    void on_sectionClicked(int column);
    void modelSorting(int column);

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    DBconnection *connection;
    QSqlQueryModel *model;
//    QThread *modelThread;
    MySortFilterProxyModel *myProxyModel;

signals:
    void modelChanged();
};

#endif // MAINWINDOW_H
