#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery>
#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_add_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO product VALUES"
                   ":name,:category)");
    query->bindValue(":name", ui->lineEdit_name->text());
    query->bindValue(":category", ui->lineEdit_category->text());

    QMessageBox*mess= new QMessageBox();
    if(!query->exec())
    {
        mess->setText("Запрос составлен неверно!");
        mess->show();
    }

    close();
}

