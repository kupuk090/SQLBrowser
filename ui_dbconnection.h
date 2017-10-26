/********************************************************************************
** Form generated from reading UI file 'dbconnection.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBCONNECTION_H
#define UI_DBCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBconnection
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelDriver;
    QComboBox *comboBox;
    QLabel *labelDB;
    QLineEdit *editDB;
    QLabel *labelUser;
    QLineEdit *editUser;
    QLabel *labelPassword;
    QLineEdit *editPassword;
    QLabel *labelHost;
    QLineEdit *editHost;
    QLabel *labelPort;
    QSpinBox *editPort;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *submitButton;
    QPushButton *clearButton;

    void setupUi(QWidget *DBconnection)
    {
        if (DBconnection->objectName().isEmpty())
            DBconnection->setObjectName(QStringLiteral("DBconnection"));
        DBconnection->resize(244, 265);
        gridLayout = new QGridLayout(DBconnection);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelDriver = new QLabel(DBconnection);
        labelDriver->setObjectName(QStringLiteral("labelDriver"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelDriver);

        comboBox = new QComboBox(DBconnection);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox);

        labelDB = new QLabel(DBconnection);
        labelDB->setObjectName(QStringLiteral("labelDB"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelDB);

        editDB = new QLineEdit(DBconnection);
        editDB->setObjectName(QStringLiteral("editDB"));

        formLayout->setWidget(1, QFormLayout::FieldRole, editDB);

        labelUser = new QLabel(DBconnection);
        labelUser->setObjectName(QStringLiteral("labelUser"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelUser);

        editUser = new QLineEdit(DBconnection);
        editUser->setObjectName(QStringLiteral("editUser"));

        formLayout->setWidget(2, QFormLayout::FieldRole, editUser);

        labelPassword = new QLabel(DBconnection);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelPassword);

        editPassword = new QLineEdit(DBconnection);
        editPassword->setObjectName(QStringLiteral("editPassword"));
        editPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, editPassword);

        labelHost = new QLabel(DBconnection);
        labelHost->setObjectName(QStringLiteral("labelHost"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelHost);

        editHost = new QLineEdit(DBconnection);
        editHost->setObjectName(QStringLiteral("editHost"));

        formLayout->setWidget(4, QFormLayout::FieldRole, editHost);

        labelPort = new QLabel(DBconnection);
        labelPort->setObjectName(QStringLiteral("labelPort"));

        formLayout->setWidget(5, QFormLayout::LabelRole, labelPort);

        editPort = new QSpinBox(DBconnection);
        editPort->setObjectName(QStringLiteral("editPort"));
        editPort->setWrapping(false);
        editPort->setButtonSymbols(QAbstractSpinBox::NoButtons);
        editPort->setMaximum(9999);
        editPort->setValue(5432);

        formLayout->setWidget(5, QFormLayout::FieldRole, editPort);


        verticalLayout->addLayout(formLayout);

        checkBox = new QCheckBox(DBconnection);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        submitButton = new QPushButton(DBconnection);
        submitButton->setObjectName(QStringLiteral("submitButton"));

        horizontalLayout->addWidget(submitButton);

        clearButton = new QPushButton(DBconnection);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        horizontalLayout->addWidget(clearButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DBconnection);

        QMetaObject::connectSlotsByName(DBconnection);
    } // setupUi

    void retranslateUi(QWidget *DBconnection)
    {
        DBconnection->setWindowTitle(QApplication::translate("DBconnection", "Form", 0));
        labelDriver->setText(QApplication::translate("DBconnection", "Driver:", 0));
        comboBox->setCurrentText(QString());
        labelDB->setText(QApplication::translate("DBconnection", "Database:", 0));
        labelUser->setText(QApplication::translate("DBconnection", "Username:", 0));
        labelPassword->setText(QApplication::translate("DBconnection", "Password:", 0));
        labelHost->setText(QApplication::translate("DBconnection", "Hostname:", 0));
        labelPort->setText(QApplication::translate("DBconnection", "Port:", 0));
        checkBox->setText(QApplication::translate("DBconnection", "Default connection", 0));
        submitButton->setText(QApplication::translate("DBconnection", "Submit", 0));
        clearButton->setText(QApplication::translate("DBconnection", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class DBconnection: public Ui_DBconnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBCONNECTION_H
