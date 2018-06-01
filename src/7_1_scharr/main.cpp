#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, const char *args[]) {
    Mat srcImage = imread("E:/VSCode/LearnOpenCV/assets/10.jpg");
    imshow("src", srcImage);
    Mat gradX, gradY;
    Scharr(srcImage, gradX, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
    Scharr(srcImage, gradY, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
    Mat absGradX, absGradY;
    // gradX = abs(gradX);
    // gradX.convertTo(absGradX, CV_8U);
    convertScaleAbs(gradX, absGradX);
    imshow("gradX", absGradX);

    convertScaleAbs(gradY, absGradY);
    imshow("gradY", absGradY);

    Mat dst;
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, dst);
    imshow("grad", dst);
    waitKey();
    return 0;
}