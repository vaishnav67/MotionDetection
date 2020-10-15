#include "staticframedifference.h"

staticframedifference::staticframedifference()
{

}
staticframedifference::~staticframedifference()
{
    cv::destroyAllWindows();
}
void staticframedifference::start()
{
    cv::Mat img_input, img_background, img_foreground;
        cv::VideoCapture cam(0);
        while (1)
        {
            cam >> img_input;
            if (img_background.empty())
                img_input.copyTo(img_background);

            cv::absdiff(img_input, img_background, img_foreground);

            if (img_foreground.channels() == 3)
                cv::cvtColor(img_foreground, img_foreground, cv::COLOR_BGR2GRAY);
            cv::imshow("Static Frame Diffrence: Input", img_input);
            cv::imshow("Static Frame Difference: Background", img_background);
            cv::imshow("Static Frame Difference: Forground", img_foreground);
            int keyboard = cv::waitKey(30);
            if (keyboard == 'q' || keyboard == 27)
                break;
        }
}
