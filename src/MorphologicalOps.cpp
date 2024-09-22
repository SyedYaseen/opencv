#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{

    Mat img = imread("./Images/j.png", 0);
    Mat eroded;
    Mat dilated;
    Mat opened;
    Mat closed;
    imshow("Original", img);
    Mat struc = cv::getStructuringElement(MORPH_RECT, cv::Size(5, 5));
    
    morphologyEx(img, eroded, MORPH_ERODE, struc);
    imshow("eroded", eroded);

    morphologyEx(img, dilated, MORPH_DILATE, struc);
    imshow("dilated", dilated);
    //open - erode + dilate
    morphologyEx(img, opened, MORPH_OPEN, struc);
    imshow("opened", opened);
    // Close - dilate + erode
    morphologyEx(img, closed, MORPH_CLOSE, struc);
    imshow("closed", closed);
    
    //Mat img = imread("./Images/morphocar.webp", 0);
    //imshow("car", img);
    //if (img.empty())
    //{
    //    return EXIT_FAILURE;
    //}

    //// define 13x5 structure that fits the plate dimensions
    //Mat structuring = getStructuringElement(MORPH_RECT, cv::Size(13, 5));
    //// cout << structuring;
    //Mat eroded = Mat::zeros(img.size(), CV_8UC1); 
    ////erode(img, eroded, structuring, cv::Point(-1, -1), 1, BORDER_DEFAULT);

    //
    //morphologyEx(img, eroded, MORPH_TOPHAT, structuring, Point(-1, -1), 1, 0, morphologyDefaultBorderValue());
    //morphologyEx(eroded, eroded, MORPH_BLACKHAT, structuring, Point(-1, -1), 3, 0, morphologyDefaultBorderValue());

    //
    //imshow("eroded", eroded);

    waitKey(0);

    return EXIT_SUCCESS;
}