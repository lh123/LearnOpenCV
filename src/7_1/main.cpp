#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

Mat srcImage, grayImage, dstImage;

Mat cannyDetectedEdges;
int cannyLowThreshold = 1;

Mat sobelGradientX, sobelGradientY;
Mat sobelAbsGradientX, sobelAbsGradientY;
int sobelKernelSize = 1;

Mat scharrGradientX, scharrGradientY;
Mat scharrAbsGradientX, scharrAbsGradientY;

void onCanny(int , void *);
void onSobel(int , void *);
void onScharr(int , void *);

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/11.jpg");
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", srcImage);

    dstImage.create(srcImage.size(), srcImage.type());
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    namedWindow("canny", WINDOW_AUTOSIZE);
    namedWindow("sobel", WINDOW_AUTOSIZE);
    namedWindow("scharr", WINDOW_AUTOSIZE);

    createTrackbar("value", "canny", &cannyLowThreshold, 120, onCanny);
    createTrackbar("value", "sobel", &sobelKernelSize, 3, onSobel);

    onCanny(0, nullptr);
    onSobel(0, nullptr);
    onScharr(0, nullptr);
    waitKey();
    return 0;
}

void onCanny(int , void *) {
    GaussianBlur(grayImage, cannyDetectedEdges, Size(3, 3), 0, 0, BORDER_DEFAULT);
    Canny(cannyDetectedEdges, cannyDetectedEdges, cannyLowThreshold, cannyLowThreshold * 3);
    dstImage = Scalar::all(0);
    srcImage.copyTo(dstImage, cannyDetectedEdges);
    imshow("canny", dstImage);
}

void onSobel(int , void *) {
    Sobel(srcImage, sobelGradientX, CV_16S, 1, 0, 2 * sobelKernelSize + 1, 1, 0, BORDER_DEFAULT);
    Sobel(srcImage, sobelGradientY, CV_16S, 0, 1, 2 * sobelKernelSize + 1, 1, 0, BORDER_DEFAULT);

    convertScaleAbs(sobelGradientX, sobelAbsGradientX);
    convertScaleAbs(sobelGradientY, sobelAbsGradientY);

    addWeighted(sobelAbsGradientX, 0.5, sobelAbsGradientY, 0.5, 0, dstImage);

    imshow("sobel", dstImage);
}

void onScharr(int , void *) {
    Scharr(srcImage, scharrGradientX, CV_16S, 1, 0);
    Scharr(srcImage, scharrGradientY, CV_16S, 0, 1);

    convertScaleAbs(scharrGradientX, scharrAbsGradientX);
    convertScaleAbs(scharrGradientY, scharrAbsGradientY);

    addWeighted(scharrAbsGradientX, 0.5, scharrAbsGradientY, 0.5, 0, dstImage);

    imshow("scharr", dstImage);
}