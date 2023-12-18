#include "modfydialog.h"
#include "ui_modfydialog.h"

ModfyDialog::ModfyDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModfyDialog)
{
    ui->setupUi(this);
    ui->label_image->setScaledContents(true);
    QSqlQuery *queryCombo = new QSqlQuery();
    queryCombo->exec("SELECT name FROM category");
    while (queryCombo->next())
    {
        ui->comboBox_category->addItem(queryCombo->value(0).toString());
    }
}

ModfyDialog::~ModfyDialog()
{
    delete ui;
}

void ModfyDialog::on_pushButton_edit_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET name = :name,"
                   "category = :category, ImagePath = :image WHERE ID = :ID");
    query->bindValue(":ID", tempID);
    query->bindValue(":name",ui->lineEdit_name->text());
    query->bindValue(":category",ui->comboBox_category->currentIndex()+1);
    query->bindValue(":image",Img);
    if(query->exec())
    {
        close();
    }
}

void ModfyDialog::sendingID(int aa)
{
    tempID = aa;
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, category, ImagePath FROM product"
                   "WHERE ID = ?");
    query->bindValue(0,aa);
    if (query->exec())
    {
        query->next();
        ui->lineEdit_name->setText(query->value(0).toString());
        ui->comboBox_category->setCurrentIndex(query->value(1).toInt()-1);
        Img = query->value(2).toString();
        ui->label_image->setPixmap(Img);
    }
}
