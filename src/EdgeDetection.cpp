#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("./Images/coins.png", 0);
    //Mat img = imread("./Images/lenna.png", 0);
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
    Mat EdgeAngles = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {
            try {

                float intensityX = 0, intensityY = 0, radians = 0, angle = 0;
                for (auto& item : sobelKernelX) {
                    intensityX += item[0] * img.at<uchar>(i + item[1], j + item[2]);
                }

                for (auto& item : sobelKernelY) {
                    intensityY += item[0] * img.at<uchar>(i + item[1], j + item[2]);
                }

                // This is finding the hypotenuse while considering sobel X as base & sobel Y as opp side
                // Intensity based on both of these is the hypotenuse

                float intensity = sqrt(intensityX * intensityX + intensityY * intensityY);
                // Clamp the intensity to stay between 0 and 255
                SobelOut.at<uchar>(i, j) = std::min(255.0f, std::max(0.0f, intensity));




                // Calculating edge direction
                angle = atan2f(intensityY, intensityX) * (180.0 / 3.14159265358979323846);
                if (angle < 0) angle += 180;

                EdgeAngles.at<uchar>(i, j) = angle;


                
            }
            catch (Exception ex) {
                int a = i;
                int b = j;
            }
        }
    }
    imshow("Angle", EdgeAngles);

    
    // Gradient magnitude thresholding or lower bound cut-off suppression (Wiki)
    // The process is that we loop over all the pixels and take two adjacent pixels of the 
    // current pixel and compare with them to find whether the intensity of the current pixel 
    // is greater than the two adjacent pixels, if so then continue, if not then set the 
    // current pixel intensity to 0. 
    // Adjacent pixels are ones that are almost perpendicular to the angle of the main pixel.
    Mat NMSOut = Mat::zeros(img.size(), CV_8UC1);
    
    for (int i = 1; i < img.rows - 1; i++) {
        for (int j = 1; j < img.cols - 1; j++) {
            float q = 255, r = 255;
            float angle = EdgeAngles.at<uchar>(i, j);

            if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180)) {

                r = SobelOut.at<uchar>(i, j - 1);
                q = SobelOut.at<uchar>(i, j + 1);
            }
            
            else if (angle >= 22.5 && angle < 67.5) {
                r = SobelOut.at<uchar>(i - 1, j + 1);
                q = SobelOut.at<uchar>(i + 1, j - 1);
            }


            else if (angle >= 67.5 && angle < 112.5) {
                r = SobelOut.at<uchar>(i - 1, j);
                q = SobelOut.at<uchar>(i + 1, j);
            }


            else if (angle >= 112.5 && angle < 157.5) {
                r = SobelOut.at<uchar>(i + 1, j + 1);
                q = SobelOut.at<uchar>(i - 1, j - 1);
            }


            if ((SobelOut.at<uchar>(i, j) >= q) && (SobelOut.at<uchar>(i, j) >= r)) {
                NMSOut.at<uchar>(i, j) = SobelOut.at<uchar>(i, j);
            }
            else
                NMSOut.at<uchar>(i, j) = 0;
        }
    }

    
    
    imshow("Before hyste", NMSOut);

    // Remove noise and make edge sharper with double threshold and hysterisis
    // Calculate high threshold by calcualting the max value of image (might use some other methods also, I want to try with this)
    Mat HysteOut = Mat::zeros(img.size(), CV_8UC1);;
    Mat hist;
    int width = 256;
    float ranges[] = { 0, 256 };
    bool uniform = true, accumulate = false;
    const float* histRange[] = { ranges };

    //Get Max value to find threshold
    calcHist(&img, 1, 0, Mat(), hist, 1, &width, histRange, uniform, accumulate);
    float histMax = 0;
    for (int i = 0; i < width; i++) {
        if (hist.at<float>(i) > histMax) histMax = hist.at<float>(i);
    }

    float highT = 70;
    float lowT = highT * 0.3;

    std::cout << endl << histMax << endl << "High Threshold: " << highT << " Low Threshold: " << lowT << std::endl;
    for (int i = 1; i < img.rows; i++) {
        for (int j = 1; j < img.cols; j++) {
            if (NMSOut.at<uchar>(i, j) >= highT) HysteOut.at<uchar>(i, j) = 255; // Strong edge
            else if (NMSOut.at<uchar>(i, j) < lowT) HysteOut.at<uchar>(i, j) = 0;
            else {
                // Weak edge check if the neighbour is a strong edge
                if (NMSOut.at<uchar>(i - 1, j - 1) >= highT ||
                    NMSOut.at<uchar>(i - 1, j) >= highT ||
                    NMSOut.at<uchar>(i - 1, j + 1) >= highT ||

                    NMSOut.at<uchar>(i, j - 1) >= highT ||
                    NMSOut.at<uchar>(i - 1, j + 1) >= highT ||

                    NMSOut.at<uchar>(i + 1, j - 1) >= highT ||
                    NMSOut.at<uchar>(i + 1, j) >= highT ||
                    NMSOut.at<uchar>(i + 1, j + 1) >= highT) 
                {
                    HysteOut.at<uchar>(i, j) = 255; // Set it as strong edge
                }
                else {
                    HysteOut.at<uchar>(i, j) = 0;
                }
            }
        }
    }

    //cout << NMSOut;
    imshow("After hystersis", HysteOut);

    //imshow("My Sobel", SobelOut);


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
    //imshow("cv sobel out", cvSobelOut);

    //Mat edges, cvEdges;
    //Canny(cvSobelOut, cvEdges, 100, 200, 3, false);
    //imshow("cv canny out", cvEdges);

    //Canny(SobelOut, edges, 100, 200, 3, false);
    //imshow("my canny Outt", edges);

    waitKey(0);

    return EXIT_SUCCESS;
}