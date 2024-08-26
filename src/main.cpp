#include <stdio.h>
#include <opencv2/highgui.hpp>
using namespace cv;

int main() {
	Mat img = imread("C:\\Users\\ssyed\\source\\repos\\OpenCvStuff\\src\\lenna.png");
	imshow("Window", img);
	waitKey(2000);
	return 0;
}