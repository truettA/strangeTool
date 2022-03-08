#include "drawimg.h"
#include <QDebug>

DrawImg::DrawImg(QObject *parent)
    : QObject{parent}
{

}

void DrawImg::recvBoxes(std::vector<cv::Rect> boxes, cv::Mat frame)
{
    cv::Mat cloneFrame = frame.clone();
    cv::cvtColor(cloneFrame, cloneFrame, cv::COLOR_RGB2BGR);
    const uchar *pSrc = (const uchar*)cloneFrame.data;
    qImage = QImage(pSrc, cloneFrame.cols, cloneFrame.rows, cloneFrame.step, QImage::Format_RGB888);
    qDebug() << "drawImg:" << cloneFrame.type() ;

}
