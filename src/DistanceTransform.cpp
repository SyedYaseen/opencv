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
	
	vector<vector<int>> disTr;
 
	int min, minIdx, val, v;
	float rootTwo = sqrtf(2);

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (disTrans.at<uchar>(i, j) == 255) disTrans.at<uchar>(i, j) = INT32_MAX;
		}
	}

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			
			val = disTrans.at<uchar>(i, j);
			if (val == INT32_MAX) continue; // already visited + ignore bg
			
			min = 0;
			minIdx = -1;
			for (int k = 0; k < topLeft.size(); k++) {
				int x = topLeft[k].x + i; int y = topLeft[k].y + j;
				if (x < 0 || x >= src.rows || y < 0 || y >= src.cols) continue;

				if (disTrans.at<uchar>(x, y) < min) {
					min = disTrans.at<uchar>(x, y);
					minIdx = i;
				}
			}

			if (minIdx == 0 || minIdx == 2) val += rootTwo; // This is diagonal pts' index from TopLeft
			else val += 1;
		}
	}



	// Second Propogation
	vector<Point> bottomRight = {
		{ 1, 1 }, { 0, 1 }, { -1, 1 },
		{ 1, 0 }
	};

	for (int i = src.rows - 1; i >= 0; i--) {
		for (int j = src.cols - 1; j >= 0; j--) {
			val = disTrans.at<uchar>(i, j);

			if (val == INT32_MAX) continue;
			min = 0;
			minIdx = -1;
			for (int k = 0; k < bottomRight.size(); k++) {
				int x = bottomRight[k].x + i; int y = bottomRight[k].y + j;
				if (x < 0 || x >= src.rows || y < 0 || y >= src.cols) continue;

				if (disTrans.at<uchar>(x, y) < min) {
					min = disTrans.at<uchar>(x, y);
					minIdx = i;
				}
			}

			if (minIdx == 0 || minIdx == 2) val += rootTwo; // This is diagonal pts' index from TopLeft
			else val += 1;

		}
	}

	cout << disTrans;

	imshow("disTrans", disTrans);
	
	
	//dilate(openOut, dilatedOut, struc, Point(-1, -1), 3);
	
	
	//distanceTransform(dilatedOut, disTrans, DIST_L2, 3, CV_8U);
	//imshow("cvDisTrans", disTrans);


	waitKey(0);
	return 0;
}