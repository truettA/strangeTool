#include "drawimg.h"

DrawImg::DrawImg(QWidget *parent)
    : QWidget{parent}
{

}

void DrawImg::drawBoxs(cv::Mat &frame, std::vector<cv::Rect> &boxes, std::vector<int> &indices, std::vector<float> &confidences)
{
    for(int i = 0; i < indices.size(); i++){
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        cv::rectangle(frame, cv::Point(box.x, box.y), cv::Point(box.x+box.width, box.y+box.height), m_rectangleColor, m_ractThickness);
        std::string label = cv::format("%.5f", confidences[idx]);
        int baseLine;
        cv::Size labelSize = cv::getTextSize(label, m_fontFace, m_fontScale, m_textThickness, &baseLine);
        int top = cv::max(box.y, labelSize.height);

    }
}
