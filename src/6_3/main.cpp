#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

// Mat outImage1 = image.clone();
// int channels = image.channels();
// for (int y = 1; y < image.rows - 1; y++) {
//     for (int x = 1; x < image.cols - 1; x++) {
//         for (int c = 0; c < channels; c++) {
//             uchar value = 255;
//             for (int i = -1; i < 2; i++) {
//                 for (int j = -1; j < 2; j++) {
//                     uchar temp = image.at<Vec3b>(y + i, x + j)[c];
//                     if (temp < value) {
//                         value = temp;
//                     }
//                 }
//             }
//             outImage1.at<Vec3b>(y, x)[c] = value;
//         }
//     }
// }

Mat srcImage;
Mat dstImage;

int selectTrackerValue = 0;
int structElementSize = 3;

void process();

int main(int argc, const char *args[]) {
    srcImage = imread("E:/VSCode/LearnOpenCV/assets/1.jpg");

    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", srcImage);

    namedWindow("dst", WINDOW_AUTOSIZE);

    createTrackbar("erode/dilate", "dst", &selectTrackerValue, 1, [](int, void *) { process(); });
    createTrackbar("value", "dst", &structElementSize, 21, [](int, void *) { process(); });
    process();
    waitKey();
    return 0;
}

void process() {
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1),
                                        Point(structElementSize, structElementSize));
    if (selectTrackerValue == 0) {
        erode(srcImage, dstImage, element);
    } else {
        dilate(srcImage, dstImage, element);
    }
    imshow("dst", dstImage);
}