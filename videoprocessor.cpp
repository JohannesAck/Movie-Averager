#include "videoprocessor.h"

VideoProcessor::VideoProcessor()
{

}

VideoProcessor::VideoProcessor(std::string filePath) :
    _filePath(filePath)
{
    _cap = cv::VideoCapture(_filePath);
}

std::vector<cv::Vec3b> VideoProcessor::calculateMeans() {
    _cap.open(_filePath);
    cv::Mat currentFrame;
    std::vector<cv::Vec3b> means; //maybe initialize with fitting size
    _cap >> currentFrame;
    int frameCounter = 1;
    while(!currentFrame.empty()) { //iterate frames
        std::cout << "Processing Frame Nr." << frameCounter++ << std::endl;
        cv::Vec3i currentFrameMean;
        //add up all pixel colors
        for(int x = 0; x < currentFrame.rows; x++) {
            for (int y = 0; y < currentFrame.cols; y++) {
                currentFrameMean[0] += currentFrame.at<cv::Vec3b>(x,y)[0];
                currentFrameMean[1] += currentFrame.at<cv::Vec3b>(x,y)[1];
                currentFrameMean[2] += currentFrame.at<cv::Vec3b>(x,y)[2];
            }
        }
        currentFrameMean[0] /= (currentFrame.cols * currentFrame.rows);
        currentFrameMean[1] /= (currentFrame.cols * currentFrame.rows);
        currentFrameMean[2] /= (currentFrame.cols * currentFrame.rows);

        means.push_back(currentFrameMean);
        _cap >> currentFrame;
    }
    return means;
}


cv::Mat* VideoProcessor::imageFromVector(std::vector<cv::Vec3b> &meanColorValues, int outputRows, int outputColumns) {
    int rows = 50;
    int columns = meanColorValues.size();
    cv::Mat* resultingImage = new cv::Mat(rows,columns,CV_8UC3);
    for(int x = 0; x < columns; x++) {
        for(int y = 0; y < rows; y++) {
            resultingImage->at<cv::Vec3b>(cv::Point(x,y)) = meanColorValues[x];
        }
    }
    cv::resize(*resultingImage, *resultingImage, cv::Size(outputColumns, outputRows));
    return resultingImage;
}
