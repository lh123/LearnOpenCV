#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void ROIAddImage();
void linearBlending();
void ROILinearBlending();

int main(int argc, const char *args[]) {
    std::cout << "1. ROIAddImage" << std::endl;
    std::cout << "2. linearBlending" << std::endl;
    std::cout << "3. ROILinearBlending" << std::endl;
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
    case 1:
        ROIAddImage();
        break;
    case 2:
        linearBlending();
        break;
    case 3:
        ROILinearBlending();
        break;
    }
    return 0;
}

void ROIAddImage() {
    Mat srcImage = imread("E:/VSCode/LearnOpenCV/assets/dota_pa.jpg");
    Mat logoImage = imread("E:/VSCode/LearnOpenCV/assets/dota_logo.jpg");
    Mat imgROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));
    Mat mask;
    cvtColor(logoImage, mask, CV_BGR2GRAY);
    logoImage.copyTo(imgROI, mask);
    imshow("ROTAddImage", srcImage);
    waitKey();
}

void linearBlending() {
    double alphaValue = 0.5;
    double betaValue = 1 - alphaValue;
    Mat srcImage1 = imread("E:/VSCode/LearnOpenCV/assets/mogu.jpg");
    Mat srcImage2 = imread("E:/VSCode/LearnOpenCV/assets/rain.jpg");
    Mat blendImage;
    addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0, blendImage);
    imshow("linearBlending", blendImage);
    waitKey();
}

void ROILinearBlending() {
    Mat srcImage = imread("E:/VSCode/LearnOpenCV/assets/dota_pa.jpg");
    Mat logoImage = imread("E:/VSCode/LearnOpenCV/assets/dota_logo.jpg");
    Mat imageROI = srcImage(Range(250, 250 + logoImage.cols), Range(200, 200 + logoImage.rows));
    addWeighted(imageROI, 0.5, logoImage, 0.3, 0, imageROI);
    imshow("ROILinearBlending", srcImage);
    waitKey();
}