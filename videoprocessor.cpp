#include "videoprocessor.h"

VideoProcessor::VideoProcessor(std::string filePath) :
    _filePath(filePath)
{
    _cap = cv::VideoCapture(_filePath);
    _totalFrameCount = (int) _cap.get(CV_CAP_PROP_FRAME_COUNT);
}


//TODO: Move to QThread
std::vector<cv::Vec3b> VideoProcessor::calculateMeans(bool quick) {
    _cap.open(_filePath);
    cv::Mat currentFrame;
    std::vector<cv::Vec3b> means;
    means.resize(_totalFrameCount);

    clock_t start = clock();

    _cap >> currentFrame;


    for(int frameCounter = 1; frameCounter < _totalFrameCount; frameCounter++) { //iterate frames till none left
        if(frameCounter % 100 == 0) { //significantly quicker than output every time
            std::cout << "Processing Frame Nr." << frameCounter << "/" << _totalFrameCount << std::endl;
        }

        cv::Vec3i currentFrameMean;


        if(currentFrame.empty()) { //ignore faulty frames
//            currentFrameMean[0] == 0;
//            currentFrameMean[1] == 0;
//            currentFrameMean[2] == 0;
            std::cout << "Fault frame enocuntered." << std::endl;
            means[frameCounter - 1] = currentFrameMean;
            _cap >> currentFrame;
            continue;
        }


        if(quick) {
            for(int x = 0; x < currentFrame.rows; x += 10) {
                for (int y = 0; y < currentFrame.cols; y += 10) {
                    currentFrameMean[0] += currentFrame.at<cv::Vec3b>(x,y)[0];
                    currentFrameMean[1] += currentFrame.at<cv::Vec3b>(x,y)[1];
                    currentFrameMean[2] += currentFrame.at<cv::Vec3b>(x,y)[2];
                }
            }
            currentFrameMean[0] /= ((currentFrame.cols * currentFrame.rows) / 100);
            currentFrameMean[1] /= ((currentFrame.cols * currentFrame.rows) / 100);
            currentFrameMean[2] /= ((currentFrame.cols * currentFrame.rows) / 100);
        } else {
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
        }

        means[frameCounter - 1] = currentFrameMean;
        _cap >> currentFrame;
    }

    clock_t end = clock();
    std::cout << "Processing Time: " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    return means;
}


cv::Mat* VideoProcessor::imageFromVector(std::vector<cv::Vec3b> &meanColorValues, int outputRows, int outputColumns) {
    int rows = 50;
    int columns = meanColorValues.size();

    cv::Mat* resultingImage = new cv::Mat(rows,columns,CV_8UC3); //Matrix of 3-Entry-uchar-vectors
    for(int x = 0; x < columns; x++) {
        for(int y = 0; y < rows; y++) {
            resultingImage->at<cv::Vec3b>(cv::Point(x,y)) = meanColorValues[x];
        }
    }
    cv::resize(*resultingImage, *resultingImage, cv::Size(outputColumns, outputRows));
    return resultingImage;
}
