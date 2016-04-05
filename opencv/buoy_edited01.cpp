#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/highgui.h>
#include "iostream"
#include "stdio.h"

using namespace cv;
using namespace std;    
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 30;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 10 * 10;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH * 4 / 5;


void morphos(Mat &thresh)
{
	Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(15, 10));
	Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);
	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}



string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void drawObject(int x, int y, Mat &frame, double myarea)
{
	//use some of the openCV drawing functions to draw crosshairs
	//on your tracked image!

	//UPDATE:JUNE 18TH, 2013
	//added 'if' and 'else' statements to prevent
	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)

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

	putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);

}



void trackFilteredObject(int &x, int &y, Mat thresh, Mat &src1){

	Mat temp;
	thresh.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) 
	{
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects<MAX_NUM_OBJECTS)
		{
			for (int index = 0; index >= 0; index = hierarchy[index][0]) 
			{
				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea)
				{
					x = moment.m10 / area;
					y = moment.m01 / area;
					objectFound = true;
					refArea = area;
				}
				else objectFound = false;
			}
			//let user know you found an object
			if (objectFound == true)
			{
				putText(src1, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
				//draw object location on screen
				drawObject(x, y, src1, refArea);
			}

		}
		else putText(src1, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}


void enhance(Mat& img)
{
	Mat output;
	long n;
	namedWindow("Resultenhance",CV_WINDOW_NORMAL);
	int v_max_b = 0, v_min_b = 0;
	int v_max_g = 0, v_min_g = 0;
	int v_max_r = 0, v_min_r = 0;
	double s1, s2;
	//int p_s1 = 15, p_s2 = 15;
	namedWindow("Parameters");
	int p_s1=0,p_s2=0;
	createTrackbar("S1", "Parameters", &p_s1, 100);
	createTrackbar("S2", "Parameters", &p_s2, 100);
	output = img.clone();
	n = img.rows*img.cols;
	int hist_r[256] = { 0 }, hist_g[256] = { 0 }, hist_b[256] = { 0 };
	v_max_b = 0; v_min_b = 0;
	v_max_g = 0; v_min_g = 0;
	v_max_r = 0; v_min_r = 0;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			hist_b[img.at<Vec3b>(i, j)[0]] = hist_b[img.at<Vec3b>(i, j)[0]] + 1;
			hist_g[img.at<Vec3b>(i, j)[1]] = hist_g[img.at<Vec3b>(i, j)[1]] + 1;
			hist_r[img.at<Vec3b>(i, j)[2]] = hist_r[img.at<Vec3b>(i, j)[2]] + 1;
		}
	}
	for (int i = 1; i < 256; i++)
	{

		hist_b[i] += hist_b[i - 1];
		hist_g[i] += hist_g[i - 1];
		hist_r[i] += hist_r[i - 1];
	}
	s1 = p_s1 / 10.0;
	s2 = p_s2 / 10.0;
	v_min_b = 0;
	v_min_g = 0;
	v_min_r = 0;
	while (hist_b[v_min_b + 1] <= (n*s1) / 100)
		v_min_b = v_min_b + 1;
	while (hist_g[v_min_g + 1] <= (n*s1) / 100)
		v_min_g = v_min_g + 1;
	while (hist_r[v_min_r + 1] <= (n*s1) / 100)
		v_min_r = v_min_r + 1;
	v_max_b = 255 - 1; v_max_g = 255 - 1; v_max_r = 255 - 1;
	while (hist_b[v_max_b - 1] > (int)n*(1 - s2 / 100))
		v_max_b = v_max_b - 1;
	if (v_max_b < 255 - 1)
		v_max_b = v_max_b + 1;
	while (hist_g[v_max_g - 1] >(int)n*(1 - s2 / 100))
		v_max_g = v_max_g - 1;
	if (v_max_g < 255 - 1)
		v_max_g = v_max_g + 1;
	while (hist_r[v_max_r - 1] >(int)n*(1 - s2 / 100))
		v_max_r = v_max_r - 1;
	if (v_max_r < 255 - 1)
		v_max_r = v_max_r + 1;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<Vec3b>(i, j)[0] < v_min_b)
				img.at<Vec3b>(i, j)[0] = v_min_b;
			if (img.at<Vec3b>(i, j)[0] > v_max_b)
				img.at<Vec3b>(i, j)[0] = v_max_b;
			if (img.at<Vec3b>(i, j)[1] < v_min_g)
				img.at<Vec3b>(i, j)[1] = v_min_g;
			if (img.at<Vec3b>(i, j)[1] > v_max_g)
				img.at<Vec3b>(i, j)[1] = v_max_g;
			if (img.at<Vec3b>(i, j)[2] < v_min_r)
				img.at<Vec3b>(i, j)[2] = v_min_r;
			if (img.at<Vec3b>(i, j)[2] > v_max_r)
				img.at<Vec3b>(i, j)[2] = v_max_r;
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			output.at<Vec3b>(i, j)[0] = ((img.at<Vec3b>(i, j)[0] - v_min_b) * 255) / (v_max_b - v_min_b);
			output.at<Vec3b>(i, j)[1] = ((img.at<Vec3b>(i, j)[1] - v_min_g) * 255) / (v_max_g - v_min_g);
			output.at<Vec3b>(i, j)[2] = ((img.at<Vec3b>(i, j)[2] - v_min_r) * 255) / (v_max_r - v_min_r);
		}
	}
	img = output;
	imshow("Resultenhance",img);
}


int main( )
{
	VideoCapture cap("vid2.mp4"); 	
	Mat gray, dst,hsv,img,src1;
	namedWindow("Result",CV_WINDOW_NORMAL);
	namedWindow("original",CV_WINDOW_NORMAL);
	int t=0,lowh = 106, highh = 255, lows = 1, highs = 256, lowv = 0, highv = 255,lowc=0,highc=500,x=0,y=0;
	namedWindow("controls",1);
	createTrackbar("lowh", "controls", &lowh, 255);
	createTrackbar("highh", "controls", &highh, 255);
	createTrackbar("lows", "controls", &lows, 255);
	createTrackbar("highs", "controls", &highs, 255);
	createTrackbar("lowv", "controls", &lowv, 255);
	createTrackbar("highv", "controls", &highv, 255);
	namedWindow("threshwin", CV_WINDOW_NORMAL);
		


	while(1)
	{
		cap>>src1;
		//img=src1;
		//threshold(src1);
	//	enhance(src1);

		Mat thresh;
		cvtColor(src1,img ,CV_BGR2HSV);
	    inRange(img,Scalar(lowh,lows,lowv),Scalar(highh,highs,highv),thresh);
	    morphos(thresh);
	    imshow("threshwin", thresh);

	  	trackFilteredObject(x,y,thresh,src1);

	    cout<<"x= "<<x<<" y= "<<y<<endl;

	 	imshow("original",src1);
	 	imshow("Result",img);
		if(waitKey(30)==27)
		break;
  	}                                       
 	return 0;	
}
