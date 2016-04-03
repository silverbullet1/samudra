#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include "QHBoxLayout"
#include <QLabel>
#include <qdebug.h>
#include <string>
#include <iostream>
#include <QFileDialog>
#include "mat_and_qimage.hpp"
#include "globals.h"
#include "trackbars.h"
#include "ui_trackbars.h"
#include "QMessageBox"
#include "qextserialport.h"

const int  MAX_NUM_OBJECTS = 100;
const int MIN_OBJECT_AREA = 10 * 10;
int FRAME_WIDTH,FRAME_HEIGHT;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH* 4 / 5;
using namespace cv;

void drawAxis(cv::Mat&, cv::Point, cv::Point, cv::Scalar, const float);
double getOrientation(const std::vector<cv::Point> &, cv::Mat&);
void writeData(char data[]);

double seconds,fps;
Mat processed_cur_frame,gray;
time_t start, end;
bool flag,flag1;
int num_frames;
QImage img, processed_img,output;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tb = new Trackbars(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}
Mat src; bool writeFlag=false;
vector<Vec4i> hierarchy;
vector<vector<Point> > contours;
double area;

void writeData(char data[])
{
    if(opened)
    {
        //qDebug("Opened");
        //qDebug("Writing ");
        //qDebug(data);
        for(int i=0;i<sizeof(data);i++)
        port->write(data, data[i]);
    }
    else
       qDebug("Failed to connect");

}

void MainWindow::Threshold()
{
    //HSV Thresholding
    cv::Mat gray;
    cvtColor(cur_frame, gray,cv::COLOR_BGR2HSV);
    inRange(cur_frame,cv::Scalar(lowh,lows,lowv),cv::Scalar(highh,highs,highv),thresh);
    QImage img = ocv::qt::mat_to_qimage_cpy(thresh,true);
    tb->ui->frame3->setPixmap(QPixmap::fromImage(img));
    tb->ui->frame3->setScaledContents(true); //For resizing
}

void MainWindow::drawObject(int x, int y, Mat &frame, double myarea)
{
    circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
    if (y - 25>0)
        line(frame, Point(x, y), Point(x, y - 25), Scalar(255, 0, 0), 2);
    else line(frame, Point(x, y), Point(x, 0), Scalar(255, 0, 0), 2);
    if (y + 25<FRAME_HEIGHT)
        line(frame, Point(x, y), Point(x, y + 25), Scalar(255, 0, 0), 2);
    else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
    if (x - 25>0)
        line(frame, Point(x, y), Point(x - 25, y), Scalar(255, 0, 0), 2);
    else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
    if (x + 25<FRAME_WIDTH)
        line(frame, Point(x, y), Point(x + 25, y), Scalar(255, 0, 0), 2);
    else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(255, 0, 0), 2);
    std::ostringstream ss1,ss2;
    ss1<<x; ss2<<y;
    putText(frame, ss1.str() + "," + ss2.str(), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
}

void MainWindow::Enhance()
{

       // READ RGB color image and convert it to Lab
       cv::Mat bgr_image = cur_frame;
       cv::Mat lab_image;
       cv::cvtColor(bgr_image, lab_image, CV_BGR2Lab);

       // Extract the L channel
       std::vector<cv::Mat> lab_planes(3);
       cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

       // apply the CLAHE algorithm to the L channel
       cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
       clahe->setClipLimit(4);
       cv::Mat dst;
       clahe->apply(lab_planes[0], dst);

       // Merge the the color planes back into an Lab image
       dst.copyTo(lab_planes[0]);
       cv::merge(lab_planes, lab_image);

      // convert back to RGB
      cv::Mat image_clahe;
      cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

      // cv::imshow("image CLAHE", image_clahe);

      QImage processed_img = ocv::qt::mat_to_qimage_cpy(image_clahe,true);
      ui->frame2->setPixmap(QPixmap::fromImage(processed_img));
      ui->frame2->setScaledContents(true); //For resizing
}

void MainWindow::trackFilteredObject(int &x, int &y, Mat &cameraFeed)
{
        Mat temp;
        Threshold();
        thresh.copyTo(temp);
        vector< vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
        double refArea = 0;
        bool objectFound = false;
        if (hierarchy.size() > 0) {
            int numObjects = hierarchy.size();
            if (numObjects<MAX_NUM_OBJECTS){
                for (int index = 0; index >= 0; index = hierarchy[index][0]) {
                    Moments moment = moments((cv::Mat)contours[index]);
                    double area = moment.m00;
                    //if the area is less than 20 px by 20px then it is probably just noise
                    //if the area is the same as the 3/2 of the image size, probably just a bad filter
                    //we only want the object with the largest area so we safe a reference area each
                    //iteration and compare it to the area in the next iteration.
                    if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                        x = moment.m10 / area;
                        y = moment.m01 / area;
                        objectFound = true;
                        refArea = area;
                    }
                    else objectFound = false;
                  }
                //let user know you found an object
                if (objectFound == true){
                    putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
                    //draw object location on screen
                    drawObject(x, y, cameraFeed, refArea);
                    std::ostringstream ss1,ss2;
                    ss1<<x; ss2<<y;
                    string s = "#(" + ss1.str() + ")" + ss2.str() + "\n";
                    char *d = strdup(s.c_str());
                    writeData(d);
                    output = ocv::qt::mat_to_qimage_cpy(cameraFeed,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
                    ui->frame2->setPixmap(QPixmap::fromImage(output));
                    ui->frame2->setScaledContents(true); //For resizing
                }

            }
            else
            {
                putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
                output = ocv::qt::mat_to_qimage_cpy(cameraFeed,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
                ui->frame2->setPixmap(QPixmap::fromImage(output));
                ui->frame2->setScaledContents(true); //For resizing

            }
        }
}
void MainWindow::on_comboBox_activated(int index)
{
    flag=flag1=false;
    if(index==0) //Open the First camera
    {
        cap.open(0);
        fps = cap.get(CV_CAP_PROP_FPS);
        FRAME_WIDTH = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        FRAME_HEIGHT = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        QString str = QDir::homePath();
        str = str + "/Stream.avi";
        VideoWriter video(str.toUtf8().constData(),CV_FOURCC('M','J','P','G'),15, Size(FRAME_WIDTH,FRAME_HEIGHT),true);
        num_frames=0;
        time(&start);
        while (waitKey(30) != 27) // Wait 30 milliseconds and check for esc key to exit
            process();
    }

    else if(index==1) //Open the second camera
    {
        for(int i=-1;i<=1;i++)
            if(!cap.open(i))
                continue;
        if(cap.isOpened())  // check if we succeeded
        {
            fps = cap.get(CV_CAP_PROP_FPS);
            FRAME_WIDTH = cap.get(CV_CAP_PROP_FRAME_WIDTH);
            FRAME_HEIGHT = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
            QString str = QDir::homePath();
            str = str + "/Stream.avi";
            VideoWriter video(str.toUtf8().constData(),CV_FOURCC('M','J','P','G'),15, Size(FRAME_WIDTH,FRAME_HEIGHT),true);
            num_frames=0;
            time(&start);
            while (waitKey(30) != 27) // Wait 30 milliseconds and check for esc key to exit
                 process();
        }
        else
        {
            QMessageBox qmb;
            qmb.setIcon(QMessageBox::Critical);
            qmb.setInformativeText("Please connect a secondary camera first!!");
            qmb.exec();
            ui->comboBox->setCurrentIndex(0);
        }
    }
    else
    {
        //Open from file
        QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),"All files(*.*)");
        std::string utf8_text = filename.toUtf8().constData();
        cap.open(utf8_text);
        if(ui->buttonGroup->checkedId()==-5 || writeFlag)
        {
        QMessageBox qmb;
        qmb.setIcon(QMessageBox::Critical);
        qmb.setInformativeText("Dude, what's the point?");
        qmb.exec();
        }
        num_frames=0;
        time(&start);
        while (waitKey(70) != 27)
             process();
        }
}

void drawAxis(Mat& img, Point p, Point q, Scalar colour, const float scale = 0.2)
{
    double angle;
    double hypotenuse;
    angle = atan2((double)p.y - q.y, (double)p.x - q.x); // angle in radians
    hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x)); //Always positive
    double degrees = (angle * 180 / CV_PI); // convert radians to degrees (0-180 range)

    if(degrees<0)
        degrees+=180;angle = CV_PI*degrees/180;
    std::ostringstream ss1;
    ss1<<degrees;
    string s = "A=";
    s += ss1.str() + "\n";
    char *d = strdup(s.c_str());
    writeData(d);
    //qDebug() << "Angle : " << degrees << endl; // angle in 0-360 degrees range

    q.x = (int)(p.x - scale * hypotenuse * cos(angle));
    q.y = (int)(p.y - scale * hypotenuse * sin(angle));
    line(img, p, q, colour, 4, CV_AA);

    p.x = (int)(q.x + 9 * cos(angle + CV_PI / 4));
    p.y = (int)(q.y + 9 * sin(angle + CV_PI / 4));
    line(img, p, q, colour, 4, CV_AA);

    p.x = (int)(q.x + 9 * cos(angle - CV_PI / 4));
    p.y = (int)(q.y + 9 * sin(angle - CV_PI / 4));
    line(img, p, q, colour, 4, CV_AA);
}

double getOrientation(const vector<Point> &pts, Mat &img)
{
    int sz = static_cast<int>(pts.size());
    Mat data_pts = Mat(sz, 2, CV_64FC1);
    for (int i = 0; i < data_pts.rows; ++i)
    {
        data_pts.at<double>(i, 0) = pts[i].x;
        data_pts.at<double>(i, 1) = pts[i].y;
    }
    PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
    Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
        static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
    vector<Point2d> eigen_vecs(2);
    vector<double> eigen_val(2);
    for (int i = 0; i < 2; ++i)
    {
        eigen_vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
            pca_analysis.eigenvectors.at<double>(i, 1));

        eigen_val[i] = pca_analysis.eigenvalues.at<double>(0, i);
    }
    circle(img, cntr, 3, Scalar(255, 0, 255), 2);
    Point p1 = cntr + 0.02 * Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
    //Point p2 = cntr - 0.02 * Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
    drawAxis(img, cntr, p1, Scalar(0, 255, 0), 1);
    double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x);
    return angle;
}


void MainWindow::lineDetect(Mat &src)
{
    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);
    vector<Vec2f> lines;
    lines.clear();
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );
    double xsum = 0.0,ysum = 0.0;
    int k = 0;
    for( size_t i = 0; i < lines.size(); i++ )
    {
         float rho = lines[i][0], theta = lines[i][1];
         Point pt1, pt2;
         double a = cos(theta), b = sin(theta);
         double x0 = a*rho, y0 = b*rho;
         pt1.x = cvRound(x0 + 1000*(-b));
         pt1.y = cvRound(y0 + 1000*(a));
         pt2.x = cvRound(x0 - 1000*(-b));
         pt2.y = cvRound(y0 - 1000*(a));
         line( cdst, pt1, pt2, Scalar(0,0,255), 4, CV_AA);
        // qDebug () << "Drawing line between (" << pt1.x<<","<<pt1.y <<"( and (" << pt2.x<<","<<pt2.y<<")";
         xsum = xsum + pt1.x + pt2.x;
         ysum = ysum + pt1.y + pt2.y;
         k++;
    }
    xsum/=k; ysum/=k;
    std::ostringstream ss1,ss2;
    ss1<<xsum; ss2<<ysum;
    string s = "$(" + ss1.str() + ")" + ss2.str() + "\n" ;
    char *d = strdup(s.c_str());
    writeData(d);
    //qDebug () << "Calculated Centroid is (" << xsum <<"," <<ysum<< ")" ;

       QImage img = ocv::qt::mat_to_qimage_cpy(cdst,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
       ui->frame2->setPixmap(QPixmap::fromImage(img));
       ui->frame2->setScaledContents(true); //For resizing
}
void MainWindow::process()
{
    cap>>cur_frame;
    img = ocv::qt::mat_to_qimage_cpy(cur_frame,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
    ui->frame1->setPixmap(QPixmap::fromImage(img));
    ui->frame1->setScaledContents(true); //For resizing
    Enhance(); // Enhance cur_frame by default
    switch(ui->buttonGroup->checkedId())
       {
         case -2: //Orange Path ✓
         src=cur_frame;
         if (!tb->isVisible() && !flag) //flag=true indicates that user pressed the EXIT button
            tb->show();  //otherwise the window won't close no matter what
         flag=true;
         flag1=false;
         Threshold();
         findContours(thresh, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
         for (size_t i = 0; i < contours.size(); ++i)
         {
                 area = contourArea(contours[i]);
                 if (area < 1e2 || 1e5 < area) continue;
                 drawContours(src, contours, static_cast<int>(i), Scalar(0, 0, 255), 2, 8, hierarchy, 0);
                 getOrientation(contours[i], src);
         }
         processed_img = ocv::qt::mat_to_qimage_cpy(src,true);
         ui->frame2->setPixmap(QPixmap::fromImage(processed_img));
         ui->frame2->setScaledContents(true); //For resizing
         break;

         case -3: //Gate detect ✓
         lineDetect(cur_frame);
         flag=flag1=false;
         break;

         case -4: //HSV Thresholding ✓
         if (!tb->isVisible() && !flag1) //Exit button not pressed yet
            tb->show();
         flag=false,flag1=true;
         Threshold();
         break;

         case -6:if (!tb->isVisible() && !flag1)  //Exit button not pressed yet
          tb->show();

         flag=false,flag1=true;
         processed_cur_frame = cur_frame;
         int a,b;
         trackFilteredObject(a,b, processed_cur_frame);
         break;
         //default:
         //output = ocv::qt::mat_to_qimage_cpy(cur_frame,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
         //ui->frame2->setPixmap(QPixmap::fromImage(output));
         //ui->frame2->setScaledContents(true); //For resizing
    }
        num_frames++;
        time(&end);
        seconds = difftime (end, start);
        fps  = num_frames / seconds;
        ui->label_6->setText(QString("%1").arg(fps));
        waitKey(1000); //1000 and 70 are self callibrated values for reading properly from file..na zada tez na zada dheere
}

void MainWindow::on_pushButton_clicked()
{
    close();
    cap.release();
}
