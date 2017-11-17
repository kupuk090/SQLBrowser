#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>

namespace Ui {
class DBconnection;
}

class DBconnection : public QDialog
{
    Q_OBJECT

public:
    explicit DBconnection(QDialog *parent = 0);
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
