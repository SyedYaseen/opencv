#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("./Images/lenna.png", 0);
    if (img.empty())
    {
        return EXIT_FAILURE;
    }


    // Sobel Kernel

    vector<std::array<int, 3>> sobelKernelX = {
        {1, -1,-1},  {0,-1,0}, {-1,-1,1},
        {2, 0,-1},   {0,0,0},  {-2,0,1},
        {1, 1,-1},   {0,1,0},  {-1,1,1}
    };


    vector<std::array<int, 3>> sobelKernelY = {
        {1, -1,-1},  {2,-1,0}, {1,-1,1},
        {0, 0,-1},   {0,0,0},  {0,0,1},
        {-1, 1,-1},  {-2,1,0}, {-1,1,1}
    };
    GaussianBlur(img, img, Size(3, 3), 0);
    imshow("Gaussian", img);

    Mat SobelOut = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {
            try {

                int intensityX = 0, intensityY = 0;
                for (auto& item : sobelKernelX) {
                    intensityX += item[0] * img.at<uchar>(i + item[1], j + item[2]);
                }
    
                for (auto& item : sobelKernelY) {
                    intensityY += item[0] * img.at<uchar>(i + item[1], j + item[2]);
                }
                int intensity = sqrt(intensityX * intensityX + intensityY * intensityY);
                SobelOut.at<uchar>(i, j) = std::min(255, std::max(0, abs(intensity)));
            }
            catch (Exception ex) {
                int a = i;
                int b = j;
            }
        }
    }
    imshow("My Sobel", SobelOut);

    Mat SobelX, SobelY, SobelXY, cvSobelOut;
    Sobel(img, SobelX, CV_64F, 1, 0, 3);
    Sobel(img, SobelY, CV_64F, 0, 1, 3);

    convertScaleAbs(SobelX, SobelX);
    convertScaleAbs(SobelY, SobelY);

    addWeighted(SobelX, 0.5, SobelY, 0.5, 0, cvSobelOut);
    //Sobel(img, cvSobelOut, CV_64F, 1, 1, 3);

    //imshow("SobelX", SobelX);
    //imshow("SobelY", SobelY);
    //imshow("SobelXY", SobelXY);
    imshow("cv sobel out", cvSobelOut);

    Mat edges, cvEdges;
    Canny(cvSobelOut, cvEdges, 100, 200, 3, false);
    imshow("cv canny out", cvEdges);

    Canny(SobelOut, edges, 100, 200, 3, false);
    imshow("my canny Outt", edges);

    waitKey(0);

    return EXIT_SUCCESS;
}