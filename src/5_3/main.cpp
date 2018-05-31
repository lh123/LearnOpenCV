#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

void multiChannelBlending(int channel);

int main(int argc, const char *args[]) {
    for (int i = 0; i < 3; i++) {
        multiChannelBlending(i);
    }
    return 0;
}

void multiChannelBlending(int channel) {
    Mat srcImage = imread("E:/VSCode/LearnOpenCV/assets/dota_jugg.jpg");
    Mat logoImage = imread("E:/VSCode/LearnOpenCV/assets/dota_logo.jpg", IMREAD_GRAYSCALE);
    std::vector<Mat> channels;
    split(srcImage, channels);

    Mat imageROI = channels[channel](Rect(500, 250, logoImage.cols, logoImage.rows));
    addWeighted(imageROI, 1.0, logoImage, 0.5, 0, imageROI);
    Mat mergeImage(srcImage.size(), srcImage.type());
    merge(channels, mergeImage);
    imshow("blending", mergeImage);
    waitKey();
}