#include "drawimg.h"
#include <QDebug>

DrawImg::DrawImg(QObject *parent)
    : QObject{parent}
{
    isShowImg = true;
}

void DrawImg::recvBoxes(std::vector<cv::Rect> boxes, std::vector<int> classIds, cv::Mat frame)
{
    qDebug() << "recvDrawing======";

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    const uchar *pSrc = (const uchar*)frame.data;
    qImage = QImage(pSrc, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    qDebug() << "drawImg:" << frame.type() ;

}
