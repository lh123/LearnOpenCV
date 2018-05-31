#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void onMedianBlur(int value, void *userData);
void onBilateralFilter(int value, void *userData);

Mat srcImage;
Mat dstImage1, dstImage2;
int medianBlurValue = 10;
int bilateralFilterValue = 10;

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/1.jpg");
    namedWindow("src");
    imshow("src", srcImage);

    namedWindow("MedianBlur");
    createTrackbar("value", "MedianBlur", &medianBlurValue, 50, onMedianBlur);
    onMedianBlur(0, nullptr);

    namedWindow("BilateralFilter");
    createTrackbar("value", "BilateralFilter", &bilateralFilterValue, 50, onBilateralFilter);
    onBilateralFilter(0, nullptr);
    waitKey();
    return 0;
}

void onMedianBlur(int value, void *userData) {
    medianBlur(srcImage, dstImage1, medianBlurValue * 2 + 1);
    imshow("MedianBlur", dstImage1);
}

void onBilateralFilter(int value, void *userData) {
    bilateralFilter(srcImage, dstImage2, bilateralFilterValue, bilateralFilterValue * 2, bilateralFilterValue / 2);
    imshow("BilateralFilter", dstImage2);
}