#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>


namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();
    QMessageBox*msg;
    QSqlDatabase*db;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
