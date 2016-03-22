#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Trackbars/trackbars.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void Enhance();
    void lineDetect(cv::Mat &img);
    void Threshold();

private slots:
    void on_comboBox_activated(int index);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Trackbars *tb;
};

#endif // MAINWINDOW_H
