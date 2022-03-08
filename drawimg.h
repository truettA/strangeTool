#ifndef DRAWIMG_H
#define DRAWIMG_H

#include <QObject>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>



class DrawImg : public QObject, public QPainter
{
    Q_OBJECT
public:
    explicit DrawImg(QObject *parent = nullptr);

public:
    QImage qImage;

public slots:
    void recvBoxes(std::vector<cv::Rect> boxes, cv::Mat frame);

signals:


};

#endif // DRAWIMG_H
