#ifndef PRINTGRAF_H
#define PRINTGRAF_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class PrintGraf;
}

class PrintGraf : public QWidget
{
    Q_OBJECT

public:
    explicit PrintGraf(QWidget *parent = nullptr);
    ~PrintGraf();

private:
    Ui::PrintGraf *ui;
    QVector <double> dx, dy;//для хранения координат точки
    double minX, minY, maxX, maxY; //для определения границ
};

#endif // PRINTGRAF_H
