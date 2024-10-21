#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
using namespace cv;


int main() {
	Mat src = imread("./Images/touchCoins.jpg", 0);
	imshow("src", src);

	Mat otsuOut;
	threshold(src, otsuOut, 0.0, 255.0, THRESH_OTSU);
	threshold(otsuOut, otsuOut, 0.0, 255.0, THRESH_BINARY_INV);
	imshow("otsuOut", otsuOut);

	Mat openOut = Mat::zeros(src.size(), CV_8UC1);
	Mat dilatedOut = Mat::zeros(src.size(), CV_8UC1);
	Mat disTrans = Mat::zeros(src.size(), CV_8UC1);
	Mat struc = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

	morphologyEx(otsuOut, openOut, MORPH_OPEN, struc);
	//morphologyEx(closeOut, dilatedOut, MORPH_DILATE, struc, Point(-1,-1), 2);
	dilate(openOut, dilatedOut, struc, Point(-1, -1), 3);
	distanceTransform(dilatedOut, disTrans, DIST_L2, 3, CV_8U);

	double minVal, maxVal;
	minMaxLoc(disTrans, &minVal, &maxVal);



	threshold(disTrans, disTrans, 0.7 * maxVal, 255.0, THRESH_BINARY);


	imshow("openOut", openOut);
	imshow("dilatedOut", dilatedOut);
	imshow("disTrans", disTrans);
	
	Mat diff = Mat::zeros(src.size(), CV_8UC1);

	diff =  dilatedOut - openOut;
	imshow("Diff", diff);
	waitKey(0);
	return 0;
}