#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>

namespace Ui {
class DBconnection;
}

class DBconnection : public QWidget
{
    Q_OBJECT

public:
    explicit DBconnection(QWidget *parent = 0);
    ~DBconnection();
    int defaultPort(QString driver);
    QSqlError addConnection(QSqlDatabase *db);

private slots:
    void on_submitButton_clicked();
    void on_clearButton_clicked();
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::DBconnection *ui;
    QSqlDatabase *db;

signals:
    void dbCorrectlyOpen(QSqlDatabase *db);
};

#endif // DBCONNECTION_H
