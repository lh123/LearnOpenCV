#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
using namespace cv;

void writeYAML();
void readYAML();

int main(int argc, const char *args[]) {
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
    case 0:
        writeYAML();
        break;
    case 1:
        readYAML();
        break;
    }
    return 0;
}

void writeYAML() {
    FileStorage fs("test.yaml", FileStorage::WRITE);

    fs << "frameCounter" << 5;
    using std::chrono::system_clock;
    std::time_t rawTime = system_clock::to_time_t(system_clock::now());
    fs << "calibratime" << std::asctime(std::localtime(&rawTime));
    double data[] = {1000, 0, 320, 0, 1000, 40, 0, 0, 1};
    Mat cameraMatrix(Size(3, 3), CV_64FC1, data);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs << "features"
       << "[";

    for (int i = 0; i < 3; i++) {
        int x = std::rand() % 640;
        int y = std::rand() % 480;
        uchar lbp = std::rand() % 256;
        fs << "{"
           << "x" << x << "y" << y << "lbp"
           << "[:";
        for (int j = 0; j < 8; j++) {
            fs << ((lbp >> j) & 0x1);
        }
        fs << "]"
           << "}";
    }
    fs << "]";
    fs.release();
}

void readYAML() {
    FileStorage fs("test.yaml", FileStorage::READ);
    int frameCounter = fs["frameCounter"];
    // fs["frameCounter"] >> frameCounter;
    std::string date = fs["calibratime"];
    Mat cameraMatrix;
    fs["cameraMatrix"] >> cameraMatrix;
    Mat distCoeffs;
    fs["distCoeffs"] >> distCoeffs;

    std::cout << "frameCounter: " << frameCounter << std::endl
              << "calibration data: " << date << std::endl
              << "camera matrix: " << cameraMatrix << std::endl
              << "distortion matrix: " << distCoeffs << std::endl;

    FileNode features = fs["features"];
    int index = 0;
    for (const FileNode &node : features) {
        std::cout << "feature #" << index << std::endl
                  << "  x=" << static_cast<int>(node["x"]) << std::endl
                  << "  y=" << static_cast<int>(node["y"]) << std::endl
                  << "  lbp: [";
        const FileNode &lbpNode = node["lbp"];
        for (size_t i = 0; i < lbpNode.size(); i++) {
            std::cout << static_cast<int>(lbpNode[i]) << " ";
        }
        std::cout << "]" << std::endl;
        index++;
    }
    fs.release();
}