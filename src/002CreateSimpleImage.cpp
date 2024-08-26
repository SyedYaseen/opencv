#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// Grey Image
	Mat grey = Mat::zeros(3, 3, CV_8UC1);
	grey.at<uchar>(0, 0) = 0;
	grey.at<uchar>(0, 1) = 100;
	grey.at<uchar>(0, 2) = 90;
	grey.at<uchar>(1, 0) = 50;
	grey.at<uchar>(1, 1) = 0;
	grey.at<uchar>(1, 2) = 5;
	grey.at<uchar>(2, 0) = 20;
	grey.at<uchar>(2, 1) = 100;
	grey.at<uchar>(2, 2) = 0;
	
	Mat BigGrey;
	resize(grey, BigGrey, cv::Size(), 100, 100, cv::INTER_NEAREST);
	imshow("Grey", BigGrey);

	// Color Image
	Mat color = Mat::zeros(3, 3, CV_8UC3);
	color.at<Vec3b>(0, 0) = Vec3b(255, 0, 0);
	color.at<Vec3b>(0, 1) = Vec3b(255, 0, 0);
	color.at<Vec3b>(0, 2) = Vec3b(100, 0, 0);
	color.at<Vec3b>(1, 0) = Vec3b(255, 0, 0);
	color.at<Vec3b>(1, 1) = Vec3b(255, 255, 0);
	color.at<Vec3b>(1, 2) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 0) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 1) = Vec3b(255, 0, 0);
	color.at<Vec3b>(2, 2) = Vec3b(255, 0, 255);

	Mat BigColor;
	resize(color, BigColor, cv::Size(), 100, 100, cv::INTER_NEAREST);
	imshow("Color", BigColor);


	waitKey(0);

	return 0;
}