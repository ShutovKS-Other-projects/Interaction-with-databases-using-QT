#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include <QSqlQueryModel>
#include "adddialog.h"
#include "ui_adddialog.h"
#include "modfydialog.h"
#include "ui_modfydialog.h"
#include "printdialog.h"
#include "ui_printdialog.h"
#include "printgraf.h"
#include "ui_printgraf.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int flag;

private slots:
    void on_connect_to_database_triggered();

    void on_disconnect_to_database_triggered();

    void on_update_database_triggered();

    void on_pushButton_filter_clicked();

    void on_pushButton_added_clicked();

    void on_pushButton_update_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_edit_clicked();

    void on_pushButton_remove_clicked();

    void CustomMenuReq(QPoint);
    void DelRecAction();
    void ModRecAction();

    void on_pushButton_export_to_word_clicked();

    void on_pushButton_export_to_pdf_clicked();

    void on_toolButton_image_clicked();

    void on_graphic_report_triggered();

signals:
    void sendID(int);

private:
    Ui::MainWindow *ui;
    ConnectionDialog *dlg;
    QSqlDatabase db;
    QMessageBox*msg;
    QSqlQueryModel *qmodel;
    AddDialog *add;
    ModfyDialog *mdlg;
    PrintDialog *pdlg;
    QString Img;
    PrintGraf *pg;
    int GlobID;
};
#endif // MAINWINDOW_H
