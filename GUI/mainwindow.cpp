#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include "QHBoxLayout"
#include <QLabel>
#include <qdebug.h>
#include <QFileDialog>
#include "mat_and_qimage.hpp"
#include "globals.h"
#include "trackbars.h"
#include "ui_trackbars.h"
#include "QMessageBox"
using namespace cv;

void drawAxis(cv::Mat&, cv::Point, cv::Point, cv::Scalar, const float);
double getOrientation(const std::vector<cv::Point> &, cv::Mat&);
double seconds,fps;
bool flag1 = false;
time_t start, end;
int num_frames;
Mat gray;
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

void MainWindow::on_comboBox_activated(int index)
{
    QImage img,processed_img;
    Mat processed_cur_frame;
    int width,height;
    bool flag=false,flag1=false;
    if(index==0) //Open the First   camera
    {
        cap.open(0);
        fps = cap.get(CV_CAP_PROP_FPS);
        width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        QString str = QDir::homePath();
        str = str + "/Stream.avi";
        VideoWriter video(str.toUtf8().constData(),CV_FOURCC('M','J','P','G'),15, Size(width,height),true);
        num_frames=0;
        time(&start);
        while (waitKey(30) != 27) // Wait 30 milliseconds and check for esc key to exit
        {
            cap>>cur_frame;
            img = ocv::qt::mat_to_qimage_cpy(cur_frame,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
            ui->frame1->setPixmap(QPixmap::fromImage(img));
            ui->frame1->setScaledContents(true); //For resizing
            //Enhance(); // Enhance cur_frame by default
            if(ui->buttonGroup->checkedId()==-5 || writeFlag)
            {
                  video.write(cur_frame);
                  writeFlag=true;
            }
            switch(ui->buttonGroup->checkedId())
            {
            case -2: //Orange Path ✓
                    src=cur_frame;
                    if (!tb->isVisible() && !flag) { //flag=true indicates that user pressed the EXIT button
                        //otherwise the window won't close no matter what
                        tb->show();
                    }
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
                     //Make another form to vary rho theta etc.
                     flag=flag1=false;
                     break;

            case -4: //HSV Thresholding ✓
                    if (!tb->isVisible() && !flag1) { //Exit button not pressed yet
                        tb->show();
                    }
                    flag=false,flag1=true;
                    Threshold();
                    break;

            }
            num_frames++;
            time(&end);
            seconds = difftime (end, start);
            fps  = num_frames / seconds;
            ui->label_6->setText(QString("%1").arg(fps));
        }
    }

    else if(index==1) //Open the second camera
    {
        for(int i=-1;i<=1;i++)
            if(!cap.open(i))
                continue;
        if(cap.isOpened())  // check if we succeeded
        {
        fps = cap.get(CV_CAP_PROP_FPS);
        width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        QString str = QDir::homePath();
        str = str + "/Stream.avi";
        VideoWriter video(str.toUtf8().constData(),CV_FOURCC('M','J','P','G'),15, Size(width,height),true);
        num_frames=0;
        time(&start);
        while (waitKey(30) != 27) // Wait 30 milliseconds and check for esc key to exit
        {
            cap>>cur_frame;
            img = ocv::qt::mat_to_qimage_cpy(cur_frame,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
            ui->frame1->setPixmap(QPixmap::fromImage(img));
            ui->frame1->setScaledContents(true); //For resizing
            //Enhance(); // Enhance cur_frame by default
            if(ui->buttonGroup->checkedId()==-5 || writeFlag)
            {
                  video.write(cur_frame);
                  writeFlag=true;
            }
            switch(ui->buttonGroup->checkedId())
            {
            case -2: //Orange Path ✓
                    src=cur_frame;
                    if (!tb->isVisible() && !flag) { //flag=true indicates that user pressed the EXIT button
                        //otherwise the window won't close no matter what
                        tb->show();
                    }
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
                     //Make another form to vary rho theta etc.
                     flag=flag1=false;
                     break;

            case -4: //HSV Thresholding ✓
                    if (!tb->isVisible() && !flag1) { //Exit button not pressed yet
                        tb->show();
                    }
                    flag=false,flag1=true;
                    Threshold();
                    break;
            }
            num_frames++;
            time(&end);
            seconds = difftime (end, start);
            fps  = num_frames / seconds;
            ui->label_6->setText(QString("%1").arg(fps));
    }
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
        while (waitKey(70) != 27)
        {
            cap>>cur_frame;
            img = ocv::qt::mat_to_qimage_cpy(cur_frame,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
            ui->frame1->setPixmap(QPixmap::fromImage(img));
            ui->frame1->setScaledContents(true); //For resizing
            waitKey(1000); //1000 and 70 are self callibrated values for reading properly from file..na zada tez na zada dheere
        }
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
    qDebug() << "Angle : " << degrees << endl; // angle in 0-360 degrees range

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
    Point p2 = cntr - 0.02 * Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
    drawAxis(img, cntr, p1, Scalar(0, 255, 0), 1);
    double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x);
    return angle;
}

void MainWindow::Enhance()
{
       cv::Mat src = cur_frame;
       cv::Mat bgr_image = src;
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
      Mat image_clahe;
      cv::cvtColor(image_clahe, src, CV_Lab2BGR);
      //cv::imshow("image CLAHE", image_clahe);
      QImage processed_img = ocv::qt::mat_to_qimage_cpy(image_clahe,true);
      ui->frame2->setPixmap(QPixmap::fromImage(processed_img));
      ui->frame2->setScaledContents(true); //For resizing
}

void MainWindow::lineDetect(Mat &src)
{
    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );
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
         line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
       QImage img = ocv::qt::mat_to_qimage_cpy(cdst,true);//Convert Mat->QImage and pass true for swapping channels(BGR->RGB)
       ui->frame2->setPixmap(QPixmap::fromImage(img));
       ui->frame2->setScaledContents(true); //For resizing
}

void MainWindow::on_pushButton_clicked()
{
    close();
    cap.release();
}

