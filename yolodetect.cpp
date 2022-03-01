#include "yolodetect.h"
#include <QDebug>
#include <vector>


yoloDetect::yoloDetect(QObject *parent):QObject(parent)
{
    qDebug() << "yoloDetect";
}

yoloDetect::yoloDetect(QString video_src, double thread)
{
    m_thread = thread;
    net = cv::dnn::readNetFromDarknet(m_modelCfg.toStdString(), m_weightsFile.toStdString());
    if(net.empty()){
        qDebug() << "net load filed!";
        throw QString("net load filed!");
    }
    net.setPreferableBackend(backendId);
    net.setPreferableTarget(targetId);


}

yoloDetect::~yoloDetect()
{

}

void yoloDetect::detctImg()
{
//    cv::Mat frame = cv::imread("/Users/tangtang/Desktop/桌面壁纸/315955-106.jpg");
//    cv::imshow("show", frame);

    qDebug() << "child thread:" << QThread::currentThread();
    if(m_frame.empty()){
        qDebug() << "m_frame is null!";
    }
    if(!boxes.empty()){
        boxes.clear();
    }
    double confidence;
    cv::Mat blob;
    double scalefactor;
    int width;
    int height;

    cv::dnn::blobFromImage(m_frame, blob, scalefactor, cv::Size(width, height), false, false, false);
    net.setInput(blob);
    std::vector<cv::Mat> outs;
    std::vector<std::string> names;
    this->getOutputNames(names);
    net.forward(outs, names);
    std::vector<int> classIds;

    for(int i = 0; i < outs.size(); i++){
        float* data = (float*)outs[i].data;
        for(int j = 0; j < outs[i].rows; j++, data += outs[i].cols){
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
            if(confidence > m_thread){
                int centerX = (int)(data[0] * m_frame.cols);
                int centerY = (int)(data[1] * m_frame.rows);
                int width = (int)(data[2] * m_frame.cols);
                int height = (int)(data[3] * m_frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }
    cv::dnn::NMSBoxes(boxes, confidences, m_thread, m_NMSThread, indices);
}

void yoloDetect::getOutputNames(std::vector<std::string> &names)
{
    if(names.empty()){
        std::vector<int> outLayers = net.getUnconnectedOutLayers();
        std::vector<std::string> layersName = net.getLayerNames();
        names.resize(outLayers.size());
        for(int i = 0; i < outLayers.size(); i++){
            names[i] = layersName[outLayers[i] - 1];
        }
    }
    return;
}
