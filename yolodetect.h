#ifndef YOLODETECT_H
#define YOLODETECT_H
#include <QVector>
#include <QString>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/dnn.hpp>





class yoloDetect
{
public:
    yoloDetect();
    yoloDetect(QString video_src);
    ~yoloDetect();

public:
    QString m_modelCfg;
    QString m_weightsFile;
    QString m_classesFile;

    int backendId;
    int targetId;

private:
    QVector<float> confidences;
    cv::dnn::Net net;

public:
    void detctImg();




};

#endif // YOLODETECT_H
