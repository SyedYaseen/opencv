#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main4() {

	Mat skittles = imread("./Images/skittles.jpg");
	
	Rect rec(100, 100, 100, 100);
	rectangle(skittles, rec, Scalar(255), 1, 8, 0);
	Mat roi = skittles(rec);

	imshow("With Rectangle", skittles);
	//imshow("Roi", roi);

	Mat transforms(2, 3, CV_64FC1);
	Mat transformedSkittles;
	warpAffine(skittles, transformedSkittles, transforms, skittles.size(), 1, 0, Scalar());
	imshow("Transformed", transformedSkittles);


	waitKey(0);

	return 0;
}