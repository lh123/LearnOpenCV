#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void onBoxFilter(int value, void *userData);
void onBlur(int value, void *userData);
void onGaussianBlur(int value, void *userData);

Mat srcImage;
Mat dstImage1, dstImage2, dstImage3;

int boxFilterValue = 3, blurValue = 3, gaussianBlurValue = 3;

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/3.jpg");

    dstImage1 = srcImage.clone();
    dstImage2 = srcImage.clone();
    dstImage3 = srcImage.clone();

    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", srcImage);

    namedWindow("BoxFilter", WINDOW_AUTOSIZE);
    createTrackbar("value", "BoxFilter", &boxFilterValue, 40, onBoxFilter);
    onBoxFilter(0, nullptr);

    namedWindow("Blur", WINDOW_AUTOSIZE);
    createTrackbar("value", "Blur", &blurValue, 40, onBlur);
    onBlur(0, nullptr);

    namedWindow("GaussianBlur", WINDOW_AUTOSIZE);
    createTrackbar("value", "GaussianBlur", &gaussianBlurValue, 40, onGaussianBlur);
    onGaussianBlur(0, nullptr);

    waitKey();
    return 0;
}

void onBoxFilter(int value, void *userData) {
    boxFilter(srcImage, dstImage1, -1, Size(boxFilterValue + 1, boxFilterValue + 1));
    imshow("BoxFilter", dstImage1);
}

void onBlur(int value, void *userData) {
    blur(srcImage, dstImage2, Size(blurValue + 1, blurValue + 1));
    imshow("Blur", dstImage2);
}

void onGaussianBlur(int value, void *userData) {
    GaussianBlur(srcImage, dstImage3, Size(gaussianBlurValue * 2 + 1, gaussianBlurValue * 2 + 1), 0, 0);
    imshow("GaussianBlur", dstImage3);
}