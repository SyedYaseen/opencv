#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;


void displayHistogram(Mat& img, const String& title) {
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

    imshow(title, histImage);
}

int mainHistoEql()
{
    Mat img = imread("./Images/lenna.png", IMREAD_GRAYSCALE);
    if (img.empty())
    {
        return EXIT_FAILURE;
    }

    //displayHistogram(img, "Original");

    Mat eql;
    equalizeHist(img, eql);
    imshow("Eqlz", eql);

    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);

    Mat dst;
    clahe->apply(img, dst);
    imshow("Orig", img);
    imshow("lena_CLAHE", dst);
    
    clahe->setClipLimit(8);
    Mat dst2;
    clahe->apply(img, dst2);
    imshow("lena_CLAHE 8", dst2);



    waitKey(0);

    return EXIT_SUCCESS;
}

/*
When we say Clip Limit = 3.0, it means that the pixel count in any bin is allowed to be at most 3 times the average bin value before clipping occurs.

Here's a detailed breakdown:

Average Bin Value : This is the total number of pixels in the image(or a sub - region of the image) divided by the number of histogram bins.
Clip Limit of 3.0 : Each bin can hold up to 3 times the average bin value.If a bin exceeds this value, the excess is clipped(removed), and the excess pixels are redistributed to other bins.
Example Calculation
Let’s say you have an image(or sub - region) with 1, 000 pixels and 256 bins(representing different intensity levels, as in an 8 - bit grayscale image).The average bin value would be :

java
Copy code
Average Bin Value = Total Pixels / Number of Bins
= 1000 / 256
? 3.9 pixels per bin
With Clip Limit = 3.0, the maximum number of pixels allowed per bin before clipping would be :

java
Copy code
Maximum Bin Value(Clip Limit) = 3.0 * Average Bin Value
= 3.0 * 3.9
? 11.7 pixels per bin
This means that any bin with more than approximately 12 pixels will be clipped.The excess pixels are then redistributed across the bins that are still below the clip limit.

Why This is Different from "3%"
Clip Limit = 3.0 refers to the factor(multiplier) of the average bin value, not a percentage.
If it were based on percentage, then a clip limit might refer to, say, bins with more than 3 % of the total pixels, but that's not what "Clip Limit 3.0" means.

*/