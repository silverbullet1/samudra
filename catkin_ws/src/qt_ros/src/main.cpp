#include "mainwindow.h"
#include <QApplication>
#include "globals.h"
#include "ros/ros.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "QT");
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    ros::spinOnce();
    app.processEvents();
    loop_rate.sleep();
    ++count; //Optionally for debugging..to keep a track of sent messages
  }
  return app.exec();
}
