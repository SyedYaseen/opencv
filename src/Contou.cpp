#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

// Thresholding used for segmentation
// Can separate foreground from background


int mainCont() {
	//Mat img = imread("./Images/coins.png", 0);
	Mat img = imread("./Images/skittles.jpg", 0);
	threshold(img, img, 0, 255, THRESH_OTSU);
	imshow("thr", img);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	// Draw all contours
	// wrong drawContours(img, contourImage, -1, cv::Scalar(150, 0, 0), 1, 8);
	
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rand() % 256, rand() % 256, rand() % 256);
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

		// Compute the convex hull for the contour
		vector<Point> hull;
		convexHull(contours[i], hull);

		drawContours(drawing, vector<vector<Point>>{hull}, -1, Scalar(0, 255, 0), 2);
	}

	// Display the result
	imshow("Contours", drawing);



	

	waitKey(0);

	return 0;
}