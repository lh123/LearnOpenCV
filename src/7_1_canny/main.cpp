#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, const char *args[]) {
    Mat src = imread("E:/VSCode/LearnOpenCV/assets/7.jpg");
    Mat grayImage, edge, dst;
    dst.create(src.size(), src.type());
    cvtColor(src, grayImage, COLOR_BGR2GRAY);
    GaussianBlur(grayImage, edge, Size(3, 3), 0, 0);
    Canny(edge, edge, 3, 9);
    dst = Scalar::all(0);
    src.copyTo(dst, edge);
    imshow("canny src", src);
    imshow("canny edge", edge);
    imshow("canny dst", dst);
    waitKey();
    return 0;
}