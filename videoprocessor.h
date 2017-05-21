#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <memory>
#include <thread>


class VideoProcessor
{
private:
    const std::string _filePath;
    cv::VideoCapture _cap;
    int _frameCount;
public:
    VideoProcessor();
    VideoProcessor(std::string _filePath);
    std::vector<cv::Vec3b> calculateMeans(bool quick = false);
    static cv::Mat* imageFromVector(std::vector<cv::Vec3b> &meanColorValues, int outputRows, int outputColumns);
};

/**
 * @brief VideoProcessor::imageFromVector
 * @param meanColorValues
 * @return shared pointer pointing to the resulting image
 */

#endif // VIDEOPROCESSOR_H
