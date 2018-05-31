#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int thresholdValue = 100;
int thresholdType = 3;
Mat srcImage, grayImage, dstImage;

void onThreshold(int, void *);

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/6.jpg");
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", srcImage);

    namedWindow("dst", WINDOW_AUTOSIZE);

    createTrackbar("type", "dst", &thresholdType, 4, onThreshold);
    createTrackbar("value", "dst", &thresholdValue, 255, onThreshold);

    onThreshold(0, nullptr);
    waitKey();
    return 0;
}

void onThreshold(int, void *) {
    threshold(grayImage, dstImage, thresholdValue, 255, thresholdType);
    imshow("dst", dstImage);
}
