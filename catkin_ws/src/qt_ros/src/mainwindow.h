#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trackbars.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

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
    void process();
private slots:
    void on_comboBox_activated(int index);
    void on_pushButton_clicked();
    void trackFilteredObject(int &x, int &y,cv::Mat &cameraFeed);
    void drawObject(int x, int y, cv::Mat &frame, double myarea);

private:
    Ui::MainWindow *ui;
    Trackbars *tb;
};

#endif // MAINWINDOW_H
