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
    Mat img = imread("./Images/lenna.png", 0);

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
    double thresh = cv::threshold(img, thresh_otsu, 0, 255, THRESH_OTSU); //
    imshow("thresh_otsu", thresh_otsu);

    Mat hist;
    int width = 256;
    
    float ranges[] = { 0, 256 };
    const float* histRange[] = { ranges };
    bool uniform = true, accumulate = false;

    calcHist(&img, 1, 0, Mat(), hist, 1, &width, histRange, uniform, accumulate);

    // OTSU Calc
    // Calculate cumulative sum avg and cumulative sum of pixels
    float cumSum[256] = { 0.0 };
    float cumPixels[256] = { 0.0 };
    cumSum[0] = 0;
    cumPixels[0] = hist.at<float>(0);
    for (int i = 1; i < width; i++) {
        cumSum[i] = (i * hist.at<float>(i)) + cumSum[i - 1]; // Cumulative sum of pixel frequency
        cumPixels[i] = cumPixels[i - 1] + hist.at<float>(i);
    }


    // Calculate threshold
    float leftWeight = 0, rightWeight = 0, leftAvg = 0, rightAvg = 0, leftVariance = 0, rightVariance = 0;
    double maxVariance = -DBL_MAX;
    double minVariance = DBL_MAX;
    int threshold;
    for (int i = 1; i < width; i++) {

        if (cumPixels[i] == 0 || cumPixels[255] - cumPixels[i] == 0) {
            continue;  // Avoid divide by Zero errors
        }
        // left
        leftWeight = cumPixels[i] / cumPixels[255];
        leftAvg = cumSum[i] / cumPixels[i];
        
        // right
        rightWeight = 1 - leftWeight;
        rightAvg = (cumSum[255] - cumSum[i]) / (cumPixels[255] - cumPixels[i]);

        // Calculate between class variance - and get Max of Variance for threshold
        double betweenClassVariance = leftWeight * rightWeight * (leftAvg - rightAvg) * (leftAvg - rightAvg);
        if (betweenClassVariance > maxVariance) {
            threshold = i;
            maxVariance = betweenClassVariance;
        }

        // Same as above but using inclass variance and get Min of Variance for threshold
        leftVariance = 0;
        for (int j = 0; j <= i; j++) {
            leftVariance += (j - leftAvg) * (j - leftAvg) * hist.at<float>(j);  // Variance contribution
        }
        leftVariance /= cumPixels[i];  // Normalize by number of pixels in class 1

        rightVariance = 0;
        for (int j = i + 1; j < 256; j++) {
            rightVariance += (j - rightAvg) * (j - rightAvg) * hist.at<float>(j);  // Variance contribution
        }
        rightVariance /= (cumPixels[255] - cumPixels[i]);  // Normalize by number of pixels in class 2

        // Total within-class variance (weighted by class size)
        double withinClassVariance = leftWeight * leftVariance + rightWeight * rightVariance;

        if (withinClassVariance < minVariance) {
            threshold = i;
            minVariance = withinClassVariance;
        }

    }

    std::cout << endl << "My calc:  " << threshold << endl << "From open cv:  " << thresh;


    // Display histogram - not necessary for OTSU calc
    //int height = 400;
    //Mat normhist;

    //cv::normalize(hist, normhist, 0, height, NORM_MINMAX, -1, Mat());

    //int binSize = 2;
    //Mat histImage = Mat::zeros(height, width * 2, CV_8UC1);
    //
    //for (int i = 1; i < width; i++) {
    //    line(histImage,
    //        Point(i * binSize, height - cvRound(normhist.at<float>(i - 1))),
    //        Point(i * binSize, height - cvRound(normhist.at<float>(i))),
    //        255, 1, 8, 0);
    //}

    //        


    //imshow("Hist", histImage);

    cv::waitKey(0);
    return 0;

}
