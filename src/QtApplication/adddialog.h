#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>

namespace Ui {
class AddDialog;
}

class AddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
