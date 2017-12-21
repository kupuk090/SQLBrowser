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


enum SortingMethods { SQL, StandartModel, MyModel };


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
    void testFunc(const QSqlQueryModel &model);
    void testFunc(StProxyModel *model);
    void testFunc(MySortFilterProxyModel *model);

private slots:
    void on_submitButton_clicked();
    void on_actionAdd_Connection_triggered();
    void getOpenedDatabase(QSqlDatabase *m_db);
    void on_sectionClicked(int column);
    void on_actionHide_vertical_headers_triggered();
    void on_revertButton_clicked();
    void on_actionQMap_triggered();
    void on_actionQuickSort_triggered();
    void on_actionHeapSort_triggered();
    void on_actionStableSort_triggered();
    void on_actionSimpleSort_triggered();
    void on_actionTimSort_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
    DBconnection *connection;
    QSqlQueryModel model;
    StProxyModel stProxyModel;
    MySortFilterProxyModel myProxyModel;
    SortingMethods choice;
    MySortingMethods sortChoice;
    bool hideFlag;

signals:
    void sortChoiceChanged(MySortingMethods ch);

};


#endif // MAINWINDOW_H
