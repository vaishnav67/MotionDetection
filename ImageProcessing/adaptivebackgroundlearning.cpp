#include "adaptivebackgroundlearning.h"

adaptivebackgroundlearning::adaptivebackgroundlearning()
{

}
adaptivebackgroundlearning::~adaptivebackgroundlearning()
{
    cv::destroyAllWindows();
}
void adaptivebackgroundlearning::start()
{
    cv::Mat img_input, img_background, img_foreground;
        cv::VideoCapture cam(0);
        while (1)
        {
            cam >> img_input;
            if (img_background.empty())
                img_input.copyTo(img_background);
            cv::Mat img_input_f(img_input.size(), CV_32F);
            img_input.convertTo(img_input_f, CV_32F, 1. / 255.);
            cv::Mat img_background_f(img_background.size(), CV_32F);
            img_background.convertTo(img_background_f, CV_32F, 1. / 255.);
            cv::Mat img_diff_f(img_input.size(), CV_32F);
            cv::absdiff(img_input_f, img_background_f, img_diff_f);
                  img_background_f = 0.05*img_input_f + (1 - 0.05)*img_background_f;
                      cv::Mat img_new_background(img_input.size(), CV_8U);
                      img_background_f.convertTo(img_new_background, CV_8U, 255.0 / (1.0 - 0.0), -0.0);
                      img_new_background.copyTo(img_background);
            img_diff_f.convertTo(img_foreground, CV_8UC1, 255.0 / (1.0 - 0.0), -0.0);
            if (img_foreground.channels() == 3)
                cv::cvtColor(img_foreground, img_foreground, cv::COLOR_BGR2GRAY);
            cv::threshold(img_foreground, img_foreground, 15, 255, cv::THRESH_BINARY);
            cv::imshow("Adaptive Background Learning: Input", img_input);
            cv::imshow("Adaptive Background Learning: Background", img_background);
            cv::imshow("Adaptive Background Learning: Forground", img_foreground);
            int keyboard = cv::waitKey(30);
            if (keyboard == 'q' || keyboard == 27)
                break;
        }
}
