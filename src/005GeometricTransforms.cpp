#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int main5() {
    Mat img = imread("./Images/lenna.png");
    Mat out;

    cout << "size: " << img.size() << endl;
    // Rotate

    // With OpenCv
    Point2f center((img.cols - 1) / 2.0, (img.rows - 1) / 2.0);
    Mat rotateMat = getRotationMatrix2D(center, 45, 1.0);
    cout << "generated" << endl << rotateMat << endl;

    // Creating the same Mat by understanding the concept
    float rotateValues[] = {
     0, 1.0, 0,
    -1.0, 0, img.rows - 1
    };
    Mat customRotateMat(2, 3, CV_32F, rotateValues);

    cout << "Custom Mat" << endl << customRotateMat << endl;

    cv::warpAffine(img, out, customRotateMat, img.size());
    imshow("out", out);

    // Translation
    int tx = 10;
    int ty = 40;
    float warpValues[] = { 1, 0, tx, 0 , 1 , ty };
    Mat transform(2, 3, CV_32F, warpValues);
    cout << "transform" << endl << transform << endl;
    Mat translateOutput;
    warpAffine(img, translateOutput, transform, img.size());
    //imshow("translate", translateOutput);

    waitKey(0);
    return 0;

}
