#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int mainMorpho()
{

    Mat img = imread("./Images/j.png", 0);
    Mat eroded;
    Mat dilated;
    Mat opened;
    Mat closed;
    imshow("Original", img);
    Mat struc = cv::getStructuringElement(MORPH_RECT, cv::Size(5, 5));
    cout << struc;

    // Struc is overlayed on top of the image
    // A foreground pixel in the input image will be kept only if all pixels inside the structuring element are > 0.
    // Otherwise, the pixels are set to 0 (i.e., background). Removing small blobs in an image or disconnecting two connected objects.
    morphologyEx(img, eroded, MORPH_ERODE, struc);
    imshow("eroded", eroded);

    // Center pixel p of the structuring element is set to white if 
    // ANY pixel in the structuring element is > 0. Dilations increase the size of foreground objects and are
    // especially useful for joining broken parts of an image together.
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