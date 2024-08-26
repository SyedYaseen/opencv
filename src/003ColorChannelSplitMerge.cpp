#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main2() {

	Mat skittles = imread("./Images/skittles.jpg");
	vector<Mat> three_channels;
	cv::split(skittles, three_channels);

	Mat zero = Mat::zeros(skittles.size(), CV_8UC1);

	Mat b = three_channels[0];
	Mat g = three_channels[1];
	Mat r = three_channels[2];

	imshow("All chan", skittles);

	Mat blue;
	Mat green;
	Mat red;

	merge(vector<Mat> {three_channels[0], zero, zero}, blue);
	merge(vector<Mat> {zero, three_channels[1], zero}, green);
	merge(vector<Mat> {zero, zero, three_channels[2]}, red);

	imshow("Window b", blue);
	imshow("Window g", green);
	imshow("Window r", red);

	waitKey(0);
	return 0;
}