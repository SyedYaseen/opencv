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
	Mat img = imread("./Images/HexMulti.png", 0);
	resize(img, img, Size(300, 300));
	imshow("orig", img);
	Mat out = Mat::zeros(img.size(), CV_8UC1);
	Mat eroded = Mat::zeros(img.size(), CV_8UC1);
	//medianBlur(img, out, 13);
	//GaussianBlur(img, out, Size(5, 5), 0);

	//morphologyEx(out, eroded, MORPH_DILATE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//Mat img = imread("./Images/skittles.jpg", 0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	//imshow("out", out);
	//imshow("img", eroded);
	Point start{ 0,0 };
	auto polarAngle = [start](Point& p1, Point& p2) {
		// start is the base point
		// p1 is the new incoming point
		// p2 is the existing point it is compared against

		// Higher the slope = Higher the polar angle
		// slope y2-y1 / x2 - x1
		// > - decresing order; < - increasing order

		// Slope(p1, start) < Slop(p2, start)
		// If false, it will swap

		int lhs = (p1.y - start.y) * (p2.x - start.x);
		int rhs = (p1.x - start.x) * (p2.y - start.y);
		if (lhs == rhs) {
			int dist1 = (p1.x - start.x) * (p1.x - start.x) + (p1.y - start.y) * (p1.y - start.y);
			int dist2 = (p2.x - start.x) * (p2.x - start.x) + (p2.y - start.y) * (p2.y - start.y);
			return dist1 < dist2;
		}
		return lhs < rhs;
	};

	Mat hull = Mat::zeros(eroded.size(), CV_8UC1);
	Mat cont = Mat::zeros(eroded.size(), CV_8UC1);

	for (auto& c : contours) {
		stack<Point> hullPoints;
		start = c[0];
		int startIndex = 0;
		for (int i = 1; i < c.size(); i++) {
			if (c[i].y < start.y || (c[i].y == start.y && c[i].x < start.x)) {
				start = c[i];
				startIndex = i;
			}
		}

		// Swap the first value with the lowest point
		swap(c[startIndex], c[0]);
		//Point temp = c[startIndex];
		//c[startIndex] = c[0];
		//c[0] = temp;

		sort(c.begin() + 1, c.end(), polarAngle); // Sort from pos 1 since we dont want o change first position
		
		for (Point p : c) {
			cont.at<uchar>(p.y, p.x) = 255;

			cont.at<uchar>(p.y - 1, p.x - 1) = 200;
			cont.at<uchar>(p.y + 1, p.x + 1) = 200;


			cont.at<uchar>(p.y + 1, p.x + 1) = 200;
			cont.at<uchar>(p.y + 1, p.x - 1) = 200;

			cont.at<uchar>(p.y - 1, p.x) = 200;
			cont.at<uchar>(p.y + 1, p.x) = 200;

			cont.at<uchar>(p.y, p.x - 1) = 200;
			cont.at<uchar>(p.y, p.x + 1) = 200;
		}

		imshow("cont", cont);

		hullPoints.push(c[0]);
		hullPoints.push(c[1]);

		for (int i = 1; i < c.size() - 1; i++) {
			Point top = hullPoints.top(); hullPoints.pop(); // check if top needs to stay
			Point secondTop = hullPoints.top();
			Point next = c[i];

			// Find determinant of vectors formed by p0 -> p1 and p0 -> p2
			Point v1(top.x - secondTop.x, top.y - secondTop.y);
			Point v2(next.x - secondTop.x, next.y - secondTop.y);
			int determinant = v1.x * v2.y - v2.x * v1.y;

			while (determinant <= 0 && hullPoints.size() > 1) {
				Point top = hullPoints.top(); hullPoints.pop();
				Point secondTop = hullPoints.top();

				v1 = Point(top.x - secondTop.x, top.y - secondTop.y);
				v2 = Point(next.x - secondTop.x, next.y - secondTop.y);
				determinant = v1.x * v2.y - v2.x * v1.y;
			}

			hullPoints.push(top);
			hullPoints.push(next);
		}

		

		while (!hullPoints.empty()) {
			Point tp = hullPoints.top();
			hull.at<uchar>(tp.y, tp.x) = 255;

	/*		hull.at<uchar>(tp.y - 1, tp.x - 1) = 200;
			hull.at<uchar>(tp.y + 1, tp.x + 1) = 200;


			hull.at<uchar>(tp.y + 1, tp.x + 1) = 200;
			hull.at<uchar>(tp.y + 1, tp.x - 1) = 200;

			hull.at<uchar>(tp.y - 1, tp.x) = 200;
			hull.at<uchar>(tp.y + 1, tp.x) = 200;

			hull.at<uchar>(tp.y, tp.x - 1) = 200;
			hull.at<uchar>(tp.y, tp.x + 1) = 200;*/

			hullPoints.pop();
		}

		imshow("hull", hull);

	}

	waitKey(0);
}