#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

Mat srcImage, dstImage, grayImage, maskImage;
int fillMode = 1;
int lowDifference = 20, upDifference = 20;
int connectivity = 4;
bool isColor = true;
bool useMask = false;
int newMaskVal = 255;

void onMouse(int event, int x, int y, int, void *) {
    if (event != EVENT_LBUTTONDOWN) {
        return;
    }
    Point seed(x, y);
    int scopeLowDifference = fillMode == 0 ? 0 : lowDifference;
    int scopeUpDifference = fillMode == 0 ? 0 : upDifference;

    int flags = connectivity + (newMaskVal << 8) + (fillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

    int b = (int)theRNG() & 255;
    int g = (int)theRNG() & 255;
    int r = (int)theRNG() & 255;

    Rect ccomp;

    Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);

    Mat dst = isColor ? dstImage : grayImage;

    int area;

    if (useMask) {
        threshold(maskImage, maskImage, 1, 128, THRESH_BINARY);
        area = floodFill(dst, maskImage, seed, newVal, &ccomp, Scalar(scopeLowDifference, scopeLowDifference, scopeLowDifference),
                         Scalar(scopeUpDifference, scopeUpDifference, scopeUpDifference), flags);
        imshow("mask", maskImage);
    } else {
        area = floodFill(dst, seed, newVal, &ccomp, Scalar(scopeLowDifference, scopeLowDifference, scopeLowDifference),
                         Scalar(scopeUpDifference, scopeUpDifference, scopeUpDifference), flags);
    }
    imshow("dst", dst);
    std::cout << "repaint count:" << area << std::endl;
}

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/5.jpg");
    srcImage.copyTo(dstImage);
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    maskImage.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);
    namedWindow("dst", WINDOW_AUTOSIZE);

    createTrackbar("lowDifference", "dst", &lowDifference, 255, nullptr);
    createTrackbar("upDifference", "dst", &upDifference, 255, nullptr);

    setMouseCallback("dst", onMouse);

    while (true) {
        imshow("dst", isColor ? dstImage : grayImage);
        int c = waitKey();
        if ((c & 255) == 27) {
            std::cout << "exit" << std::endl;
            break;
        }
        switch (c) {
        case '1':
            if (isColor) {
                cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
                maskImage = Scalar::all(0);
                isColor = false;
            } else {
                srcImage.copyTo(dstImage);
                maskImage = Scalar::all(0);
                isColor = true;
            }
            break;
        case '2':
            if (useMask) {
                destroyWindow("mask");
                useMask = false;
            } else {
                namedWindow("mask", WINDOW_KEEPRATIO);
                maskImage = Scalar::all(0);
                imshow("mask", maskImage);
                useMask = true;
            }
            break;

        case '3':
            srcImage.copyTo(dstImage);
            cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
            maskImage = Scalar::all(0);
            break;
        case '4':
            fillMode = 0;
            break;
        case '5':
            fillMode = 1;
            break;
        case '6':
            fillMode = 2;
            break;
        case '7':
            connectivity = 4;
            break;
        case '8':
            connectivity = 8;
            break;
        }
    }

    return 0;
}
