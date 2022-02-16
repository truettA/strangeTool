#include "yolodetect.h"
#include <QDebug>

yoloDetect::yoloDetect()
{
//    cv::Mat frame = cv::imread("/Users/tangtang/Desktop/桌面壁纸/315955-106.jpg");
//    cv::imshow("show", frame);



}

yoloDetect::yoloDetect(QString video_src)
{
    net = cv::dnn::readNetFromDarknet(m_modelCfg.toStdString(), m_weightsFile.toStdString());
    if(net.empty()){
        qDebug() << "net load filed!";
        throw QString("net load filed!");
    }
    net.setPreferableBackend(backendId);
    net.setPreferableTarget(targetId);

}

void yoloDetect::detctImg()
{
    double confidence;
}
