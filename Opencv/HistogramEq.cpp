#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/highgui.h>
#include "iostream"
#include "stdio.h"

using namespace cv;
using namespace std;    
 
Mat thresh,src,src1,src_gray;
vector<Mat> ch;
int highh = 59, lowh = 10, highs = 255	, lows = 146, highv = 255, lowv = 167; //Values for orange colour (temporary)
int a=0,b=0,c=0;
int threshval = 100,max_threshval = 255;
int p_s1 = 15,p_s2 = 15;
RNG rng(12345);
const string trackbarWindowName = "Trackbars";

void thresh_callback(int, void*);
void on_trackbar(int, void*)
{
	//This function gets called whenever a
	// trackbar position is changed
}

void CreateTrackbars()
	{
		//----------------------Enhancement Trackbars------------------------------------------------
		namedWindow(trackbarWindowName, 1);
		char TrackbarName[50];
		printf(TrackbarName, "p_s1", p_s1);
		printf(TrackbarName, "p_s1", p_s1);
		createTrackbar("p_s1", trackbarWindowName, &p_s1, 200, on_trackbar);
		createTrackbar("p_s2", trackbarWindowName, &p_s2, 200, on_trackbar);

		//----------------------Orange Path Orientation Trackbards------------------------------------
		namedWindow("Controls", 1);
		namedWindow("Thresh", WINDOW_NORMAL);
		createTrackbar("lowh", "controls", &lowh, 255);
		createTrackbar("highh", "controls", &highh, 255);
		createTrackbar("lows", "controls", &lows, 255);
		createTrackbar("highs", "controls", &highs, 255);
		createTrackbar("lowv", "controls", &lowv, 255);
		createTrackbar("highv", "controls", &highv, 255);	
	}


void Enhance(Mat& img)
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
//-------------------Enhancement end-----------------------

void drawAxis(Mat&, Point, Point, Scalar, const float);
double getOrientation(const vector<Point> &, Mat&);

void threshold(Mat hsv)
{	
	cvtColor(hsv, hsv, CV_BGR2HSV);
    int t=0,lowh = 0, highh = 9, lows = 132, highs = 194, lowv = 161, highv = 240,lowc=0,highc=500;
	namedWindow("controls",1);
    createTrackbar("lowh", "controls", &lowh, 255);
	createTrackbar("highh", "controls", &highh, 255);
	createTrackbar("lows", "controls", &lows, 255);
	createTrackbar("highs", "controls", &highs, 255);
	createTrackbar("lowv", "controls", &lowv, 255);
	createTrackbar("highv", "controls", &highv, 255);
	namedWindow("threshwin", CV_WINDOW_OPENGL);
	cvtColor(hsv,hsv,COLOR_BGR2HSV);
	// while(1)
    // {
    inRange(hsv,Scalar(lowh,lows,lowv),Scalar(highh,highs,highv),thresh);
    //  imshow( "Original image", thresh);  

	imshow("threshwin", thresh);
     // }
}

void morphos(Mat &thresh)
{
	Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
	Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);
	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}

//----------------------Backup plan for image enhancement-----------------------
/*void Enhance(Mat &src1)
{
	int a=0,b=0,c=0;
	split(src1,ch);
	normalize(ch[0],ch[0],a,255,NORM_MINMAX);
	normalize(ch[1],ch[1],b,255,NORM_MINMAX);
	normalize(ch[2],ch[2],c,255,NORM_MINMAX);
	equalizeHist(ch[0],ch[0]);
	equalizeHist(ch[2],ch[2]);
	equalizeHist(ch[1],ch[1]);
	merge(ch,src1);
}*/

void OrangePathOrientation(Mat &src)
{
		Mat gray;
		cvtColor(src, gray, COLOR_BGR2HSV);
		Mat bw;
		inRange(gray, Scalar(lowh, lows, lowv), Scalar(highh, highs, highv), bw);
		namedWindow("Threshold",CV_WINDOW_NORMAL);
		imshow("Threshold", bw);
		vector<Vec4i> hierarchy;
		vector<vector<Point> > contours;
		findContours(bw, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
		for (size_t i = 0; i < contours.size(); ++i)
		{
			double area = contourArea(contours[i]);
			if (area < 1e2 || 1e5 < area) continue;
			drawContours(src, contours, static_cast<int>(i), Scalar(0, 0, 255), 2, 8, hierarchy, 0);
			getOrientation(contours[i], src);
		}
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

void drawAxis(Mat& img, Point p, Point q, Scalar colour, const float scale = 0.2)
{
    double angle;
	double hypotenuse;
	angle = atan2((double)p.y - q.y, (double)p.x - q.x); // angle in radians
	hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x)); //Always positive
    double degrees = (angle * 180 / CV_PI); // convert radians to degrees (0-180 range)
    
	if(degrees<0)
		degrees+=180;angle = CV_PI*degrees/180;
	cout << "Angle : " << degrees << endl; // angle in 0-360 degrees range
	
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

//------------------Orange path Orientation end-------------------------

int main( )
{
	VideoCapture cap("vid.mp4"); 	
   	Mat gray, dst,hsv,img,src1;
	namedWindow("Result",CV_WINDOW_NORMAL);
	namedWindow("orig",CV_WINDOW_NORMAL);
	while(1)
	{
	cap>>src1;
	img=src1;
	Enhance (src1);
	OrangePathOrientation(src1);
 	imshow("Result",src1);
 	imshow("orig",img);
	if(waitKey(30)==27)
	break;
  	}                                       
 return 0;	
}
