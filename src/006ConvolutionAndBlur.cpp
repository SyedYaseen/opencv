#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int main() {
    Mat img = imread("./Images/lenna.png");
    Mat bw;

    cvtColor(img, bw, COLOR_BGR2GRAY);
    
    imshow("Orig", img);
    imshow("Bw", bw);

    vector<pair<int, int>> neigh = {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1}, {0,0}, {0,1},
        {1,-1}, {1,0}, {1,1}
    };

    Mat out = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 1; i < bw.rows - 1; i++) {
        for (int j = 1; j < bw.cols - 1; j++) {
            int intensity = 0;
            for (pair<int, int> item : neigh) {
                intensity += bw.at<uchar>(i + item.first, j + item.second);
            }
            out.at<uchar>(i, j) = intensity / neigh.size();
        }
    }
    imshow("out", out);


    vector<std::array<int, 3>> Gaussian = {
        {1,-1,-1},  {2,-1,0}, {1,-1,1},
        {2,0,-1},   {4,0,0},  {2,0,1},
        {1,1,-1},   {2,1,0},  {1,1,1}
    };

    Mat gaussianOut = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 1; i < bw.rows - 1; i++) {
        for (int j = 1; j < bw.cols - 1; j++) {
            int intensity = 0;
            for (auto& item : Gaussian) {
                intensity += item[0] * bw.at<uchar>(i + item[1], j + item[2]);
            }
            gaussianOut.at<uchar>(i, j) = intensity / 16;
        }
    }
    imshow("Gaussian", gaussianOut);


    vector<std::array<int, 3>> Edge = {
    {-1,-1,-1},  {0,-1,0}, {1,-1,1},
    {-1,0,-1},   {0,0,0},  {1,0,1},
    {-1,1,-1},   {0,1,0},  {1,1,1}
    };

    Mat edges = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 1; i < bw.rows - 1; i++) {
        for (int j = 1; j < bw.cols - 1; j++) {
            int intensity = 0;
            for (auto& item : Edge) {
                intensity += item[0] * gaussianOut.at<uchar>(i + item[1], j + item[2]);
            }
            edges.at<uchar>(i, j) = intensity / 50;
        }
    }
    imshow("edges", edges);

    waitKey(0);
    return 0;

}
