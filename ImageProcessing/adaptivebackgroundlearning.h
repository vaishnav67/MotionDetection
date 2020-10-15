#ifndef ADAPTIVEBACKGROUNDLEARNING_H
#define ADAPTIVEBACKGROUNDLEARNING_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

class adaptivebackgroundlearning
{
public:
    adaptivebackgroundlearning();
    void start();
    ~adaptivebackgroundlearning();
};

#endif // ADAPTIVEBACKGROUNDLEARNING_H
