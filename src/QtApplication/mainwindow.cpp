#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    flag = 0;
    connect(ui->tableView,
            SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(CustomMenuReq(QPoint)));
    qmodel = new QSqlTableModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_to_database_triggered()
{
    db = QSqlDatabase::addDatabase("QODBC");
    dlg = new ConnectionDialog();
    dlg->db = &db;
    dlg->show();
}

void MainWindow::on_disconnect_to_database_triggered()
{
    msg = new QMessageBox();

    if(db.isOpen())
    {
        db.close();
        msg->setText("Соединение c базой данных разорвано");
    }
    else
    {
        msg->setText("Нет установленного соединения с базой данных");
    }

    msg->show();
}

void MainWindow::on_pushButton_update_clicked()
{
    flag = 1;
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("SELECT *"
                     "FROM product a inner join category b on a.category = b.ID");
    ui->tableView->setModel(qmodel);
}

void MainWindow::on_update_database_triggered()
{
    MainWindow::on_pushButton_update_clicked();
}

void MainWindow::on_pushButton_filter_clicked()
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(qmodel);
    ui->tableView->setModel(proxyModel);

    proxyModel->setFilterKeyColumn(2);
    proxyModel->setFilterRegExp(ui->lineEdit_filter->text());
}

void MainWindow::on_pushButton_added_clicked()
{
    add = new AddDialog();
    add->show();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_ID;
    temp_ID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT name, category, ImagePath FROM product WHERE ID = :ID");
    query->bindValue(":ID",temp_ID);
    ui->lineEdit_id->setText(QString::number(temp_ID));
    if (query->exec())
    {
        query->next();
        ui->lineEdit_name->setText(query->value(0).toString());
        ui->lineEdit_category->setText(query->value(1).toString());
        Img = query->value(2).toString();
        ui->label_image->setPixmap(Img);
    }
}


void MainWindow::on_pushButton_edit_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("UPDATE product SET name = :name, "
                   "category = :category WHERE ID = :ID");
    query->bindValue(":ID",ui->lineEdit_id->text());
    query->bindValue(":name",ui->lineEdit_name->text());
    query->bindValue(":category",ui->lineEdit_category->text());
    query->bindValue(":image",Img);

    query->exec();

    ui->lineEdit_id->setText("");
    ui->lineEdit_name->setText("");
    ui->lineEdit_category->setText("");
    ui->label_image->setText("");

    MainWindow::on_pushButton_update_clicked();
}


void MainWindow::on_pushButton_remove_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID = :ID");
    query->bindValue(":ID",ui->lineEdit_id->text());
    query->exec();
    //очищаем поля ввода
    ui->lineEdit_id->setText("");
    ui->lineEdit_name->setText("");
    ui->lineEdit_category->setText("");
    ui->label_image->setText("");
    //вызов обраотчика кнопки «Обновить»
    MainWindow::on_pushButton_update_clicked();
}

void MainWindow::CustomMenuReq(QPoint pos)
{
    if (flag == 1)
    {
        QModelIndex index = ui->tableView->indexAt((pos));
        GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

        QMenu*menu = new QMenu(this);
        QAction*izm = new QAction("Изменить", this);
        connect(izm, SIGNAL(triggered()), this, SLOT(ModRecAction()));

        QAction*ud = new QAction("Удалить", this);
        connect(ud, SIGNAL(triggered()), this, SLOT(DelRecAction()));

        menu->addAction(izm);
        menu->addAction(ud);
        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::DelRecAction()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID = :ID");
    query->bindValue(":ID",GlobID);
    query->exec();
    MainWindow::on_pushButton_update_clicked();
}

void MainWindow::ModRecAction()
{
    mdlg = new ModfyDialog();
    connect(this,SIGNAL(sendID(int)),mdlg, SLOT(sendingID(int)));
    emit sendID(GlobID);
    mdlg->show();
    disconnect(this,SIGNAL(sendID(int)),mdlg,
               SLOT(sendingID(int)));
}


void MainWindow::on_pushButton_export_to_word_clicked()
{
    pdlg = new PrintDialog();
    pdlg->show();
}


void MainWindow::on_pushButton_export_to_pdf_clicked()
{
    QString str;
    str.append("<html><head></head><body><center>"
               +QString("Пример создания отчёта"));
    str.append("<table border=1><tr>");
    str.append("<td>"+QString("ID")+"</td>");
    str.append("<td>"+QString("Наименование")+"</td>");
    str.append("<td>"+QString("Категория")+"</td></tr>");
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT * FROM product");
    query->next();
    while(query->next())
    {
        str.append("<tr>");
        str.append("<td>"
                   +QString(query->value(0).toString())+"</td>");
        str.append("<td>"
                   +QString(query->value(1).toString())+"</td>");
        str.append("<td>"
                   +QString(query->value(2).toString())
                   +"</td></tr>");
    }
    str.append("</table>");
    str.append("</center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path = QFileDialog::getSaveFileName(NULL,"Сохранить", "Отчёт","PDF(*.pdf)");
    if (path.isEmpty()) return;
    printer.setOutputFileName(path);
    QTextDocument doc;
    doc.setHtml(str);
    doc.print(&printer);
}


void MainWindow::on_toolButton_image_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл",Img,"*.jpg");
    ui->label_image->setPixmap(Img);
}


void MainWindow::on_graphic_report_triggered()
{
    pg = new PrintGraf();
    pg->show();
}

