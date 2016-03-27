#include "mainwindow.h"
#include <QApplication>
#include "qextserialport.h"
#include "globals.h"
int main(int argc, char *argv[])
{
    port = new QextSerialPort("/dev/ttyUSB0");
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    port->setTimeout(0);
    opened = port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
