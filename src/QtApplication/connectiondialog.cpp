#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked()
{
    db->setDatabaseName("DRIVER={SQL Server};SERVER=" +
                       ui->lineEdit->text() +
                       ";DATABASE=" +
                       ui->lineEdit_2->text() +
                       ";");

    db->setPassword(ui->lineEdit_3->text());

    db->setPassword(ui->lineEdit_4->text());

    msg = new QMessageBox();

    if(db->open())
    {
        msg->setText("Соединение установлено");
    }
    else
    {
        QSqlError lastError = db->lastError();
        QString errorText = "Соединение НЕ установлено. Ошибка: " + lastError.text();
        msg->setText(errorText);
    }

    msg->show();
}


