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

	Mat disTrans = Mat::zeros(src.size(), CV_8UC1);
	Mat cvDisTrans = Mat::zeros(src.size(), CV_8UC1);
	
	Mat struc = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	
	threshold(src, disTrans, 0.0, 255.0, THRESH_OTSU);
	morphologyEx(disTrans, disTrans, MORPH_CLOSE, struc, Point(-1,-1), 3);
	imshow("disTrans", disTrans);

	// First Propogation
	vector<Point> topLeft = {
		{ -1, -1 }, { 0, -1 }, { 1, -1 },
		{ -1, 0 }
	};

	int min, val, v;

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			
			val = disTrans.at<uchar>(i, j);
			if (val != 0) continue; // already visited + ignore bg
			min = 0;

			for (Point& p : topLeft) {
				int x = p.x + i; int y = p.y + i;
				if (x < 0 || x >= src.rows || y < 0 || y >= src.cols) continue;

				val = disTrans.at<uchar>(x, y);


				
			}
		}
	}



	// Second Propogation
	vector<Point> bottomRight = {
		{ 1, 1 }, { 0, 1 }, { -1, 1 },
		{ 1, 0 }
	};

	for (int i = src.rows - 1; i >= 0; i--) {
		for (int j = src.cols - 1; j >= 0; j--) {

		}
	}



	
	
	//dilate(openOut, dilatedOut, struc, Point(-1, -1), 3);
	
	
	//distanceTransform(dilatedOut, disTrans, DIST_L2, 3, CV_8U);
	//imshow("cvDisTrans", disTrans);


	waitKey(0);
	return 0;
}