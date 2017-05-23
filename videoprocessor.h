#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <ctime>


class VideoProcessor
{
private:
    const std::string _filePath;
    /**
     * @brief The opencv videocapture object from which single frames are pulled
     */
    cv::VideoCapture _cap;
    int _totalFrameCount;
public:
    VideoProcessor() = delete;
    /**
     * @brief Constructs a Videoprocessor object, and updates _totalFrameCount
     * @param _filePath
     */
    VideoProcessor(std::string _filePath);
    /**
     * @brief Calculates the mean color value of each frame and adds it to a vector
     * @param If true only 1 percent of all pixels is sampled, difference usually unnoticable
     * @return Vector of mean colors from first to last frame
     */
    std::vector<cv::Vec3b> calculateMeans(bool quick = false);
    /**
     * @brief Calculates an output image from mean color vector
     * @param Usually Provided by calculateMeanas
     * @param Rows (y-Length) of output file
     * @param Columns (x-Length) of output file
     * @return vector to calculated image as cv Matrix
     */
    static cv::Mat* imageFromVector(std::vector<cv::Vec3b> &meanColorValues, int outputRows, int outputColumns);
};


#endif // VIDEOPROCESSOR_H
