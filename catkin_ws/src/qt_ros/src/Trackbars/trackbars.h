#ifndef TRACKBARS_H
#define TRACKBARS_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"

namespace Ui {
class Trackbars;
}

class Trackbars : public QMainWindow
{
    Q_OBJECT

public:
    explicit Trackbars(QWidget *parent = 0);
    Ui::Trackbars *ui;
    ~Trackbars();

private slots:
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // TRACKBARS_H
