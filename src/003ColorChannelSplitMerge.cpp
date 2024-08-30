#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main3() {
	// Each color image is made of three colors - three channels - Blue, Green, Red

	Mat img = imread("./Images/lenna.png");
	imshow("Lenna", img);

	vector<Mat> threeChannels;
	split(img, threeChannels);

	//imshow("Blue channel", threeChannels[0]);
	//imshow("Green channel", threeChannels[1]);
	//imshow("Red channel", threeChannels[2]);

	Mat zero = Mat::zeros(img.size(), CV_8UC1);
	Mat blue;
	Mat green;
	Mat red;

	merge(vector<Mat>{threeChannels[0], zero, zero}, blue);
	merge(vector<Mat>{zero, threeChannels[1], zero}, green);
	merge(vector<Mat>{zero, zero, threeChannels[2]}, red);

	//imshow("Blue channel", blue);
	//imshow("Green channel", green);
	//imshow("Red channel", red);

	Mat output;
	merge(vector<Mat>{threeChannels[0], threeChannels[1], threeChannels[2]}, output);
	imshow("Merged output", output);





	waitKey(0);
	return 0;
}