#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main2() {
	// An image is basically a matrix
	// Greyscale image - Mat contains brightness value (0 - 255) ranging between black and white
	// Color image - Mat contains brightness values for three basic colors - Blue, Green, Red

	Mat grey = Mat::zeros(3, 3, CV_8UC1);
	grey.at<uchar>(0, 0) = 0;
	grey.at<uchar>(0, 1) = 0;
	grey.at<uchar>(0, 2) = 255;
	grey.at<uchar>(1, 0) = 0;
	grey.at<uchar>(1, 1) = 100;
	grey.at<uchar>(1, 2) = 70;
	grey.at<uchar>(2, 0) = 0;
	grey.at<uchar>(2, 1) = 50;
	grey.at<uchar>(2, 2) = 0;

	Mat resizedGrey;
	resize(grey, resizedGrey, cv::Size(), 100, 100, INTER_NEAREST);

	//imshow("Grey image", resizedGrey);





	Mat color = Mat::zeros(3, 3, CV_8UC3);
	color.at<Vec3b>(0, 0) = Vec3b(255, 0, 0);
	color.at<Vec3b>(0, 1) = Vec3b(0, 255, 0);
	color.at<Vec3b>(0, 2) = Vec3b(0, 0, 255);
	color.at<Vec3b>(1, 0) = Vec3b(100, 120, 0);
	color.at<Vec3b>(1, 1) = Vec3b(120, 50, 100);
	color.at<Vec3b>(1, 2) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 0) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 1) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 2) = Vec3b(255, 0, 0);
	Mat resizedColor;
	resize(color, resizedColor, cv::Size(), 100, 100, INTER_NEAREST);

	imshow("Color image", resizedColor);

	waitKey(0);

	return 0;
}