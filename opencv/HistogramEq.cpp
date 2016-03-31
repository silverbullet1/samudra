#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
 
using namespace cv;
using namespace std;
     
 
Mat thresh,src;
void threshold(Mat hsv)
{	cvtColor(hsv, hsv, CV_BGR2HSV);
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
     {	inRange(hsv,Scalar(lowh,lows,lowv),Scalar(highh,highs,highv),thresh);
    //  imshow( "Original image", thresh);  
	 	imshow("threshwin", thresh);
      }
}

//void splitf()
void morphos(Mat &thresh){

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);



}



int main( )
{
 Mat src1;
 src1 = imread("water2.jpg", CV_LOAD_IMAGE_COLOR);
 GaussianBlur(src1,src1,Size(5,5),1.5);
 Mat gray, dst,hsv;
 vector<Mat> ch; 
 // convert to grvector<Mat> ch; a
 cvtColor(src1,hsv,CV_BGR2HSV);
 namedWindow( "Original image", CV_WINDOW_OPENGL );
 namedWindow( "b h", CV_WINDOW_OPENGL );
 namedWindow( "g s", CV_WINDOW_OPENGL );
 namedWindow( "r v", CV_WINDOW_OPENGL );
 namedWindow( "eq b", CV_WINDOW_OPENGL );
// namedWindow( "eq r", CV_WINDOW_OPENGL );
imshow( "Original image", src1);
split(hsv,ch);
imshow( "b h", ch[0]);
imshow( "g s", ch[1]);
imshow( "r v", ch[2]);
// equalizeHist(ch[0],ch[0]);
 //equalizeHist(ch[2],ch[2]);
 normalize(ch[0],ch[0],0,255,NORM_MINMAX);
  normalize(ch[1],ch[1],0,255,NORM_MINMAX);
   normalize(ch[2],ch[2],0,255,NORM_MINMAX);
 merge(ch,src1);
 imshow("bgr merge", src1);
// imshow("eq r",ch[2]);
cvtColor(src1,src1,CV_HSV2BGR);
imshow( "eq b", src1);
waitKey(0);                                       
 return 0;
}
