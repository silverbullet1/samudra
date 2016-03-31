#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<cv.h>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

double getOrientation(vector<Point> &pts, Mat &img)
{
    //Construct a buffer used by the pca analysis
    Mat data_pts = Mat(pts.size(), 2, CV_64FC1);
    for (int i = 0; i < data_pts.rows; ++i)
    {
        data_pts.at<double>(i, 0) = pts[i].x;
        data_pts.at<double>(i, 1) = pts[i].y;
    }
 
    //Perform PCA analysis
    PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
 
    //Store the position of the object
    Point pos = Point(pca_analysis.mean.at<double>(0, 0),
                      pca_analysis.mean.at<double>(0, 1));
 
    //Store the eigenvalues and eigenvectors
    vector<Point2d> eigen_vecs(2);
    vector<double> eigen_val(2);
    for (int i = 0; i < 2; ++i)
    {
        eigen_vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
                                pca_analysis.eigenvectors.at<double>(i, 1));
 
        eigen_val[i] = pca_analysis.eigenvalues.at<double>(0, i);
    }
 
    // Draw the principal components
    circle(img, pos, 3, CV_RGB(255, 0, 255), 2);
    line(img, pos, pos + 0.02 * Point(eigen_vecs[0].x * eigen_val[0], eigen_vecs[0].y * eigen_val[0]) , CV_RGB(255, 255, 0));
    line(img, pos, pos + 0.02 * Point(eigen_vecs[1].x * eigen_val[1], eigen_vecs[1].y * eigen_val[1]) , CV_RGB(0, 255, 255));
 
    return atan2(eigen_vecs[0].y, eigen_vecs[0].x);
}
int main()
{
	Mat bw, img = imread("img.jpg");
	cvtColor(img, bw, COLOR_BGR2GRAY);
	// Apply thresholding;
threshold(bw, bw, 150, 255, CV_THRESH_BINARY);
 
// Find all the contours in the thresholded image
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
findContours(bw, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
for (size_t i = 0; i < contours.size(); ++i)
{
    // Calculate the area of each contour
    double area = contourArea(contours[i]);
    // Ignore contours that are too small or too large
    if (area < 1e2 || 1e5 < area) continue;
 
    // Draw each contour only for visualisation purposes
    drawContours(img, contours, i, CV_RGB(255, 0, 0), 2, 8, hierarchy, 0);
    // Find the orientation of each shape
    //getOrientation(contours[i], img);
}
}
