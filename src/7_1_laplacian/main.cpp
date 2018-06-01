#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, const char *args[]) {
    Mat src = imread("E:/VSCode/LearnOpenCV/assets/9.jpg");
    imshow("src", src);
    Mat srcGray;
    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(src, srcGray, COLOR_BGR2GRAY);
    Mat dst, absDst;
    Laplacian(srcGray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(dst, absDst);
    imshow("dst", absDst);
    waitKey();
    return 0;
}