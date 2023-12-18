#ifndef MODFYDIALOG_H
#define MODFYDIALOG_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class ModfyDialog;
}

class ModfyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModfyDialog(QWidget *parent = nullptr);
    ~ModfyDialog();

private slots:
    void on_pushButton_edit_clicked();
    void sendingID(int);

private:
    Ui::ModfyDialog *ui;
    int tempID;
    QString Img;
};

#endif // MODFYDIALOG_H
