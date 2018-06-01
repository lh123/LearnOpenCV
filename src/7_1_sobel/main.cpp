#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, const char *args[]) {
    Mat src = imread("E:/VSCode/LearnOpenCV/assets/8.jpg");
    imshow("src", src);
    Mat gradX, gradY;
    Mat absGradX, absGradY;
    Sobel(src, gradX, CV_16S, 1, 0, 3, 1, 1);
    convertScaleAbs(gradX, absGradX);
    imshow("gradX", absGradX);

    Sobel(src, gradY, CV_16S, 1, 0, 3, 1, 1);
    convertScaleAbs(gradY, absGradY);
    imshow("gradY", absGradY);

    Mat dst;
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, dst);
    imshow("grad", dst);
    waitKey();
    return 0;
}