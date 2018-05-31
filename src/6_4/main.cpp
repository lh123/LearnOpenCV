#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

MorphShapes mShape = MORPH_RECT;
Mat srcImage;
Mat dstImage;

int morphShapesSelect = 0;
int trackbarValue = 3;
int type = 0;

void onOpenClose();
void onErodeDilate();
void onTopBlackHat();
void onGradient();

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/3.jpg");
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", srcImage);

    auto process = [](int, void *) {
        if (type == 0) {
            onOpenClose();
        } else if (type == 1) {
            onErodeDilate();
        } else if (type == 2) {
            onTopBlackHat();
        } else {
            onGradient();
        }
    };

    namedWindow("dst", WINDOW_AUTOSIZE);
    createTrackbar("type", "dst", &type, 3, process);
    createTrackbar("shape", "dst", &morphShapesSelect, 2, process);
    createTrackbar("value", "dst", &trackbarValue, 21, process);
    onOpenClose();
    waitKey();
    return 0;
}

void onOpenClose() {
    int offset = trackbarValue - 10;
    int absOffset = std::abs(offset);
    Mat element = getStructuringElement(mShape + morphShapesSelect, Size(absOffset * 2 + 1, absOffset * 2 + 1),
                                        Point(absOffset, absOffset));
    if (offset < 0) {
        morphologyEx(srcImage, dstImage, MORPH_OPEN, element);
    } else {
        morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);
    }
    imshow("dst", dstImage);
}

void onErodeDilate() {
    int offset = trackbarValue - 10;
    int absOffset = std::abs(offset);
    Mat element = getStructuringElement(mShape + morphShapesSelect, Size(absOffset * 2 + 1, absOffset * 2 + 1),
                                        Point(absOffset, absOffset));
    if (offset < 0) {
        morphologyEx(srcImage, dstImage, MORPH_ERODE, element);
    } else {
        morphologyEx(srcImage, dstImage, MORPH_DILATE, element);
    }
    imshow("dst", dstImage);
}
void onTopBlackHat() {
    int offset = trackbarValue - 10;
    int absOffset = std::abs(offset);
    Mat element = getStructuringElement(mShape + morphShapesSelect, Size(absOffset * 2 + 1, absOffset * 2 + 1),
                                        Point(absOffset, absOffset));
    if (offset < 0) {
        morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);
    } else {
        morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);
    }
    imshow("dst", dstImage);
}

void onGradient() {
    int offset = trackbarValue - 10;
    int absOffset = std::abs(offset);
    Mat element = getStructuringElement(mShape + morphShapesSelect, Size(absOffset * 2 + 1, absOffset * 2 + 1),
                                        Point(absOffset, absOffset));
    morphologyEx(srcImage, dstImage, MORPH_GRADIENT, element);
    imshow("dst", dstImage);
}