#ifndef YOLODETECT_H
#define YOLODETECT_H
#include <QVector>
#include <QString>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/dnn.hpp>
#include <QObject>
#include <QThread>




class yoloDetect:public QObject
{
public:
    yoloDetect(QObject *parent = nullptr);
    yoloDetect(QString video_src, double thread);
    ~yoloDetect();




public:
    QString m_modelCfg;
    QString m_weightsFile;
    QString m_classesFile;

    int backendId;
    int targetId;
    double m_thread;
    double m_NMSThread;

    std::vector<cv::Rect> boxes;
    std::vector<int> indices;

private:
    std::vector<float> confidences;
    cv::dnn::Net net;
    cv::Mat m_frame;

public:
    void detctImg();
    void getOutputNames(std::vector<std::string> &names);






};

#endif // YOLODETECT_H
