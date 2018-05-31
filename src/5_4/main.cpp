#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void onContrastAndBrightChange(int value, void *userData);

int contrastValue;
int brightValue;
Mat srcImage, dstImage;

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/2.jpg");
    dstImage = Mat::zeros(srcImage.size(), srcImage.type());
    contrastValue = 80;
    brightValue = 80;
    namedWindow("resultImage", WINDOW_AUTOSIZE);
    namedWindow("srcImage", WINDOW_AUTOSIZE);

    createTrackbar("Contrast", "resultImage", &contrastValue, 300, onContrastAndBrightChange);
    createTrackbar("Bright", "resultImage", &brightValue, 300, onContrastAndBrightChange);

    onContrastAndBrightChange(0, nullptr);
    waitKey();
    return 0;
}

void onContrastAndBrightChange(int value, void *userData) {
    for (int y = 0; y < srcImage.rows; y++) {
        for (int x = 0; x < srcImage.cols; x++) {
            Vec3b &dstPixel = dstImage.at<Vec3b>(y, x);
            Vec3b &srcPixel = srcImage.at<Vec3b>(y, x);
            for (int c = 0; c < 3; c++) {
                dstPixel[c] = saturate_cast<uchar>(srcPixel[c] * 0.01 * contrastValue + brightValue);
            }
        }
    }
    imshow("srcImage", srcImage);
    imshow("resultImage", dstImage);
}