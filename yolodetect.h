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
    Q_OBJECT

public:
    yoloDetect(QObject *parent = nullptr);
    yoloDetect(const QString &videoFile, const  QString &modelCfg, const QString &weightsFile, const QString &classesFile);
    ~yoloDetect();


public:
    QString m_videoFile;
    QString m_modelCfg;
    QString m_weightsFile;
    QString m_classesFile;

    int backendId;
    int targetId;
    double m_thread;
    double m_NMSThread;
    double scalefactor;

public:
    std::vector<cv::Rect> boxes;
    std::vector<int> indices;

private:
    std::vector<float> confidences;
    cv::dnn::Net net;
    cv::Mat m_frame;
    cv::VideoCapture cap;
    int m_width;
    int m_height;

private:
    void getOutputNames(std::vector<std::string> &names);

public:
    bool init();
    void detctImg();


signals:
    void sendBoxes(std::vector<cv::Rect> boxes, cv::Mat frame);


};

#endif // YOLODETECT_H
