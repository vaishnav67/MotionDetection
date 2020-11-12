#include <opencv2\opencv.hpp>
#include <vector>

int main(int argc, char* argv[])
{
    cv::VideoCapture cam(0);
    cv::Mat3b frame1;
    cv::Mat3b frame2;
    cv::Mat3b img_fg;
    cv::Mat1b fmask;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    while(1)
    {
        cam >> frame1;
        cam >> frame2;
        //cv::imshow("Input Frame 1", frame1);
        //cv::imshow("Input Frame 2", frame2);
        double fps = cam.get(cv::CAP_PROP_FPS);
        std::cout << "Frames per second of webcam: " << fps << std::endl;
        cv::absdiff(frame2, frame1, img_fg);
        //cv::imshow("Abs Diff", img_fg);
        if (img_fg.channels() == 3)
            cv::cvtColor(img_fg, fmask, cv::COLOR_RGB2GRAY);
        //cv::imshow("RGB to Gray", fmask);
        cv::threshold(fmask, fmask, 6, 255, cv::THRESH_BINARY);
        cv::imshow("Before Opening", fmask);
        morphologyEx(fmask, fmask, cv::MORPH_OPEN, kernel);
        std::vector<std::vector<cv::Point>> contours;
        findContours(fmask.clone(), contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        if (!contours.empty())
        {
            int idx_largest_contour = -1;
            double area_largest_contour = 0.0;
            for (int i = 0; i < contours.size(); ++i)
            {
                double area = contourArea(contours[i]);
                if (area_largest_contour < area)
                {
                    area_largest_contour = area;
                    idx_largest_contour = i;
                }
            }
            if (area_largest_contour > 200)
            {
                cv::Rect roi = boundingRect(contours[idx_largest_contour]);
                drawContours(frame2, contours, idx_largest_contour, cv::Scalar(0, 0, 255));
                rectangle(frame2, roi, cv::Scalar(0, 255, 0));
            }
        }
        cv::putText(frame2, std::to_string((int)fps), cv::Point(7, 70), cv::FONT_HERSHEY_SIMPLEX, 2, (100, 255, 0), 3, cv::LINE_AA);
        cv::imshow("Result", frame2);
        cv::imshow("Mask", fmask);
        if (cv::waitKey(30) >= 0) break;
    }
    return 0;
}