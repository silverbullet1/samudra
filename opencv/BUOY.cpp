#include <sstream>
#include <string>
//#include <iostream>
//#include <opencv/highgui.h>
//#include <stdio.h>
//#include <cv.h>
//#include <highgui.h>
#include <math.h>
#include <fstream>

#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include"cv.hpp"
#include <ctype.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 154;
int H_MAX = 184;
int S_MIN = 169;
int S_MAX =239;
int V_MIN = 120;
int V_MAX = 255;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS = 100;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 10 * 10;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH * 4 / 5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";
void on_trackbar(int, void*)
{//This function gets called whenever a
	// trackbar position is changed





}
string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}
void createTrackbars(){
	//create window for trackbars


//	namedWindow(trackbarWindowName, 0);
	//create memory to store trackbar name on window
//	char TrackbarName[50];
	//sprintf(TrackbarName, "H_MIN", H_MIN);
	//sprintf(TrackbarName, "H_MAX", H_MAX);
	//sprintf(TrackbarName, "S_MIN", S_MIN);
	//sprintf(TrackbarName, "S_MAX", S_MAX);
	//sprintf(TrackbarName, "V_MIN", V_MIN);
	//sprintf(TrackbarName, "V_MAX", V_MAX);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	/*createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
*/
	namedWindow("controls", 1);
	createTrackbar("H_MIN", "controls", &H_MIN, 255);
	createTrackbar("H_MAX", "controls", &H_MAX, 255);
	createTrackbar("S_MIN", "controls", &S_MIN, 255);
	createTrackbar("S_MAX", "controls", &S_MAX, 255);
	createTrackbar("V_MIN", "controls", &V_MIN, 255);
	createTrackbar("V_MAX", "controls", &V_MAX, 255);


}
void drawObject(int x, int y, Mat &frame, double myarea){

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
void morphOps(Mat &thresh){

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
void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
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

			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}
int main(int argc, char* argv[])
{
	//int t=1;
	float z;
	char com[4];
	//FILE * fp;
	//fp = _fsopen("D:\out.txt", "w+", _SH_DENYWR);
	std::ofstream outfile, hkhl;
	//outfile.open("/home/samudra/Desktop/creation.txt", ios::out);
	if (!outfile)
	{
		cout << "error opening file" << endl;
	}
	//some boolean variables for different functionality within this
	//program
	bool trackObjects = true;
	bool useMorphOps = false;
	//Matrix to store each frame of the webcam feed
	Mat cameraFeed;
	//matrix storage for HSV image
	Mat HSV;
	//matrix storage for binary threshold image
	Mat threshold;
	//x and y values for the location of the object
	int x = 0, y = 0;
	//create slider bars for HSV filtering
	createTrackbars();
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	capture.open(1);
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	
	while (1){
		hkhl.open("/home/samudra/Desktop/creation.txt", std::ofstream::out | std::ofstream::app);
		//store image to matrix
		capture.read(cameraFeed);
		//convert frame from BGR to HSV colorspace
		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
		//filter HSV image between values and store filtered image to
		//threshold matrix
		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
		//perform morphological operations on thresholded image to eliminate noise
		//and emphasize the filtered object(s)
		if (useMorphOps)
			morphOps(threshold);
		//pass in thresholded frame to our object tracking function
		//this function will return the x and y coordinates of the
		//filtered object
		if (trackObjects)
			trackFilteredObject(x, y, threshold, cameraFeed);

		//show frames 
		imshow(windowName2, threshold);
		imshow(windowName, cameraFeed);
		imshow(windowName1, HSV);
		cout << " " << x << " " << y << "\n";
		//delay 30ms so that screen can refresh.
		//image will not appear without this waitKey() command
		z = sqrt(pow((320 - x), 2) + pow((240 - y), 2));
		if (x == 0 && y == 0)
		{
			cout << "R0R";
			strcpy(com, "R0R");
			hkhl << "hk\n";
		}
		else if (z <= 140)
		{
			cout << "F0F";
			strcpy(com, "F0F");
			hkhl << "hl\n";
		}
		else if (x>300 && x <= 340 && y >= 0 && y <= 240)
		{
			cout << "U0F";
			strcpy(com, "U0F");
				hkhl << "hl\n";
		}
		else if (x>300 && x <= 340 && y>240 && y <= 480)
		{
			cout << "D0F";
			strcpy(com, "D0F");
			hkhl << "hk\n";
		}
		else if (y>220 && y <= 260 && x >= 0 && x <= 320)
		{
			cout << "L0F";
			strcpy(com, "L0F");
			hkhl << "hl\n";
		}
		else if (y>220 && y <= 260 && x>320 && x <= 640)
		{
			cout << "R0F";
			strcpy(com, "R0F");
			hkhl << "hk\n";
		}
		else if (x >= 0 && x <= 320 && y >= 0 && y <= 240)
		{
			cout << "LUF";
			strcpy(com, "LUF");
			hkhl << "hl\n";
		}
		else if (x>320 && x<640 && y >= 0 && y <= 240)
		{
			cout << "RUF";
			strcpy(com, "RUF");
			hkhl << "hl\n";
		}
		else if (x >= 0 && x <= 320 && y>240 && y<480)
		{
			cout << "LDF";
			strcpy(com, "LDF");
			hkhl << "hl\n";
		}
		else if (x>320 && x<640 && y>240 && y<480)
		{
			cout << "RDF";
			strcpy(com, "RDF");
			hkhl << "hl\n";
		}
		outfile << "!" << com << "$\n";
		
		/*t = t + 1;
		fprintf(fp, "%d\n", t);
		fflush(fp);*/
		flush(outfile);
		flush(hkhl);
		if (waitKey(30) == 27)
			break;
		hkhl.close();
	}
	outfile.close();
	
	return 0;
}
