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
	Mat img = imread("./Images/coins.png", 0);
	//Mat img = imread("./Images/skittles.jpg", 0);
	threshold(img, img, 0, 255, THRESH_OTSU);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

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
		return (p1.y - start.y) * (p2.x - start.x) < (p1.x - start.x) * (p2.y - start.y);
	};

	for (auto& c : contours) {
		stack<Point> hullPoints;
		start = c[0];
		int startIndex = -1;
		for (int i = 0; i < c.size(); i++) {
			if (c[i].y < start.y || (c[i].y == start.y && c[i].x < start.x)) {
				start = c[i];
				startIndex = i;
			}			
		}

		// Swap the first value with the lowest point
		Point temp = c[startIndex];
		c[startIndex] = c[0];
		c[0] = temp;

		sort(c.begin() + 1, c.end(), polarAngle); // Sort from pos 1 since we dont want o change first position
		
		Point p0, p1, p2;
		p0 = c[0];
		p1 = c[1];
		p2 = c[2];

		hullPoints.push(p0);
		hullPoints.push(p1);

		for (int i = 1; i < c.size() - 1; i++) {
			// Find determinant of vectors formed by p0 -> p1 and p0 -> p2
			Point v1(p1.x - p0.x, p1.y - p0.y);
			Point v2(p2.x - p0.x, p2.y - p0.y);
			int determinant = v1.x * v2.y - v2.x * v2.y;

			if (determinant <= 0) {
				hullPoints.pop();
				hullPoints.push(p2);
				p1 = p2;
				p2 = c[i + 1];
			}
			else {
				hullPoints.push(p2);
				p0 = p1;
				p1 = p2;
				p2 = c[i + 1];
			}
		}

	}

	waitKey(0);
}