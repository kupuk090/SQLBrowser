#include "dbconnection.h"
#include "ui_dbconnection.h"
#include <QDebug>

DBconnection::DBconnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DBconnection)
{
    ui->setupUi(this);

    db = new QSqlDatabase();
    QStringList drivers = QSqlDatabase::drivers();
    ui->comboBox->addItems(drivers);
    ui->comboBox->setCurrentText("QPSQL");
}

DBconnection::~DBconnection()
{
    delete ui;
}

int DBconnection::defaultPort(QString driver)
{
    if (!(QString::compare(driver,"QPSQL",Qt::CaseInsensitive)))
        return 5432;
    else
        return 0;
}

QSqlError DBconnection::addConnection(QSqlDatabase *db)
{
    QSqlError err;

    if (!db->open())
        err = db->lastError();

    return err;
}

void DBconnection::on_submitButton_clicked()
{
    QString Driver = ui->comboBox->currentText();
    QString DBname = ui->editDB->text();
    QString UserName = ui->editUser->text();
    QString Password = ui->editPassword->text();
    QString HostName = ui->editHost->text();
    int Port = ui->editPort->value();
    if ((DBname.isEmpty()) || (HostName.isEmpty()) || (UserName.isEmpty()))
    {
        QMessageBox::information(this, tr("Information about the database is incomplete"),
                                 tr("Please check the entered information and try again"));
        return;
    }

    *db = QSqlDatabase::addDatabase(Driver);
    db->setDatabaseName(DBname);
    db->setUserName(UserName);
    db->setPassword(Password);
    db->setHostName(HostName);
    db->setPort(Port);

    QSqlError err = addConnection(db);
    if (err.type() != QSqlError::NoError)
    {
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                   "opening the connection: ") + err.text());
    }
    else
    {
        emit dbCorrectlyOpen(db);
        qDebug() << "сигнал испущен";
    }
    return;
}

void DBconnection::on_clearButton_clicked()
{
    ui->editDB->clear();
    ui->editHost->clear();
    ui->editPassword->clear();
    ui->editUser->clear();
    ui->editPort->setValue(defaultPort(ui->comboBox->currentText()));

    return;
}

void DBconnection::on_checkBox_stateChanged(int arg1)
{
    if (arg1)
    {
        ui->comboBox->setCurrentText("QPSQL");
        ui->editDB->setText("demo");
        ui->editUser->setText("postgres");
        ui->editPassword->setText("110713wtf");
        ui->editHost->setText("localhost");
        ui->editPort->setValue(defaultPort("QPSQL"));

        ui->submitButton->setFocus();
    }
    else
        on_clearButton_clicked();

    return;
}
