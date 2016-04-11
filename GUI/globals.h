#ifndef GLOBALS_H
#define GLOBALS_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include "qextserialport.h"

extern int highh,lowh,highs,lows,highv,lowv,rho,theta,threshold; //Values for orange colour (temporary),
extern cv::VideoCapture cap;
extern cv::Mat cur_frame;
extern cv::Mat thresh;
extern QextSerialPort * port;
extern bool opened;

#endif // GLOBALS_H
