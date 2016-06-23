#include "mainwindow.h"
#include <QApplication>
#include "globals.h"
#include "ros/ros.h"
# ifndef QStringLiteral
# define QStringLiteral(str) QString::fromUtf8("" str "", sizeof(str) - 1)
# endif

# ifndef QByteArrayLiteral
# define QByteArrayLiteral(str) QByteArray(str, sizeof(str) - 1)
# endif
int main(int argc, char **argv)
{
  ros::init(argc, argv, "QT");
  n = new ros::NodeHandle();
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
