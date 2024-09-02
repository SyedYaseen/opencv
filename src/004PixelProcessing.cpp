#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main4() {
	Mat img = imread("./Images/lenna.png");

	Mat img_copy;
	img.copyTo(img_copy);

	Mat bw = Mat::zeros(img.size(), CV_8UC1);

	int width = img.size().width;
	int height = img.size().height;
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Vec3b current = img_copy.at<Vec3b>(i, j); // 64,100,100 
			img_copy.at<Vec3b>(i, j) = Vec3b(current[0] * 2, current[1] * 2, current[2] * 2); // 32,50,50 -- Reducing intensity by 2 

			bw.at<uchar>(i, j) = 0.2 * current[0] + 0.4 * current[1] + 0.5 * current[2];
		}
	}
	Mat cvtOutput;
	cvtColor(img, cvtOutput, COLOR_BGR2GRAY);

	imshow("Original", img);
	imshow("Modified", img_copy);
	imshow("bw", bw);
	imshow("cvt", cvtOutput);

	waitKey(0);
	return 0;
}