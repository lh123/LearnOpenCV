#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, const char *args[]) {
    Mat srcImage = imread("E:/VSCode/LearnOpenCV/assets/1.jpg", 0);
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);

    Mat padded;
    copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat floatPadded(padded.size(), CV_32FC(padded.channels()));
    padded.convertTo(floatPadded, CV_32F, 1 / 255.0f);
    Mat planes[] = {floatPadded, Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);

    split(complexI, planes);

    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage);

    //-2    1111 1110
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;

    Mat q0 = magnitudeImage(Rect(0, 0, cx, cy));
    Mat q1 = magnitudeImage(Rect(cx, 0, cx, cy));
    Mat q2 = magnitudeImage(Rect(0, cy, cx, cy));
    Mat q3 = magnitudeImage(Rect(cx, cy, cx, cy));

    Mat temp;
    q0.copyTo(temp);
    q3.copyTo(q0);
    temp.copyTo(q3);

    q1.copyTo(temp);
    q2.copyTo(q1);
    temp.copyTo(q2);

    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    imshow("magnitudeImage", magnitudeImage);
    waitKey();
    return 0;
}