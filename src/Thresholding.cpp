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

int main() {
    Mat img = imread("./Images/Lemon.jpg", 0);

    Mat thresh_bin_255;
    cv::threshold(img, thresh_bin_255, 120.0, 255, THRESH_BINARY); // Converts stricty to ether zero or 1 based on threshold value
    //imshow("ThreshBinary_255", thresh_bin_255);

    Mat thresh_trunc;
    cv::threshold(img, thresh_trunc, 200, 255, THRESH_TRUNC); // Max intensity is threshold, lesser values remain unchanged
    //imshow("thresh_trunc", thresh_trunc);

    Mat thresh_tozero;
    cv::threshold(img, thresh_tozero, 200, 255, THRESH_TOZERO); // Anything below threshold is 0 or black, above remains unchanged // THRESH_TOZERO_INV - Reverse of this
    //imshow("thresh_tozero", thresh_tozero);

    Mat thresh_otsu; // Notes on ipad
    cv::threshold(img, thresh_otsu, 0, 255, THRESH_OTSU); // 
    imshow("thresh_otsu", thresh_otsu);

    
    //Mat thresh_bin_100;
    //cv::threshold(img, thresh_bin_100, 100.0, 255, THRESH_BINARY);
    //imshow("thresh_bin_100", thresh_bin_100);
    //
    //Mat thresh_mask;
    //cv::threshold(img, thresh_mask, 120.0, 255, THRESH_MASK);
    //imshow("ThreshMask", thresh_mask);

    waitKey(0);
    return 0;

}
