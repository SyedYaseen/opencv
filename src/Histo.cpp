#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("./Images/lenna.png", IMREAD_COLOR);
    if (img.empty())
    {
        return EXIT_FAILURE;
    }

    vector<Mat> bgrPlanes;
    split(img, bgrPlanes);

    int width = 256;
    int height = 400;
    float ranges[] = { 0, 256 };
    const float* histRange[] = { ranges };

    Mat bHist, gHist, rHist;
    bool uniform = true, accumulate = false;
    
    calcHist(&bgrPlanes[0], 1, 0, Mat(), bHist, 1, &width, histRange, uniform, accumulate);
    calcHist(&bgrPlanes[1], 1, 0, Mat(), gHist, 1, &width, histRange, uniform, accumulate);
    calcHist(&bgrPlanes[2], 1, 0, Mat(), rHist, 1, &width, histRange, uniform, accumulate);

    normalize(bHist, bHist, 0, height, NORM_MINMAX, -1, Mat());
    normalize(gHist, gHist, 0, height, NORM_MINMAX, -1, Mat());
    normalize(rHist, rHist, 0, height, NORM_MINMAX, -1, Mat());
    
    int binSize = 2;

    Mat histImage(height, width * 2, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 1; i < width; i++) {
        line(histImage,
            Point(i * binSize, height - cvRound(bHist.at<float>(i - 1))),
            Point(i * binSize, height - cvRound(bHist.at<float>(i))),
            Scalar(255, 0, 0), 1, 8, 0);

        line(histImage,
            Point(i * binSize, height - cvRound(gHist.at<float>(i - 1))),
            Point(i * binSize, height - cvRound(gHist.at<float>(i))),
            Scalar(0, 255, 0), 1, 8, 0);

        line(histImage,
            Point(i * binSize, height - cvRound(rHist.at<float>(i - 1))),
            Point(i * binSize, height - cvRound(rHist.at<float>(i))),
            Scalar(0, 0, 255), 1, 8, 0);
    }

    imshow("Histo", histImage);

    waitKey(0);

    return EXIT_SUCCESS;
}