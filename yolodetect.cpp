#include "yolodetect.h"
#include <QDebug>
#include <vector>
#include <QMessageBox>


yoloDetect::yoloDetect(QObject *parent):QObject(parent)
{
    qDebug() << "yoloDetect";
}

yoloDetect::yoloDetect(const QString &videoFile,const  QString &modelCfg,const QString &weightsFile, const QString &classesFile, double thread)
{

    m_videoFile = videoFile;
    m_modelCfg = modelCfg;
    m_weightsFile = weightsFile;
    m_classesFile = classesFile;
    m_thread = thread;
    scalefactor = 1/255.0;


}

yoloDetect::~yoloDetect()
{

}

void yoloDetect::detctImg()
{
//    cv::Mat frame = cv::imread("/Users/tangtang/Desktop/桌面壁纸/315955-106.jpg");
//    cv::imshow("show", frame);

    qDebug() << "child thread:" << QThread::currentThread();

    double confidence;
    cv::Mat blob;

    int width = 512;
    int height = 288;


    while(true){
        cap.read(m_frame);
        if(m_frame.empty()){
            qDebug() << "m_frame is null!";
        }
        if(!boxes.empty()){
            boxes.clear();
        }
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
        cv::imshow("show", m_frame);
    }



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

bool yoloDetect::init()
{
    net = cv::dnn::readNetFromDarknet(m_modelCfg.toStdString(), m_weightsFile.toStdString());
    if(net.empty()){
        qDebug() << "net load filed!";
        throw QString("net load filed!");
    }
    net.setPreferableBackend(backendId);
    net.setPreferableTarget(targetId);
    if(cap.open(m_videoFile.toStdString())){
        qDebug() << "open video faild!!!";
        QMessageBox::warning(nullptr, "ERROR","open video faild!!!",QMessageBox::Yes);
    }else{
        /*
          需要添加异常处理
         */
    }

    m_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    m_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);



}

//void yoloDetect::sendBoxes(std::vector<cv::Rect> boxes)
//{

//}
