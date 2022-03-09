#include "yolodetect.h"
#include <QDebug>
#include <vector>
#include <QMessageBox>


yoloDetect::yoloDetect(QObject *parent):QObject(parent)
{
    qDebug() << "yoloDetect";
}

yoloDetect::yoloDetect(const QString &videoFile,const  QString &modelCfg,const QString &weightsFile, const QString &classesFile)
{

    m_videoFile = videoFile;
    m_modelCfg = modelCfg;
    m_weightsFile = weightsFile;
    m_classesFile = classesFile;
    m_thread = 0.4;
    m_NMSThread = 0.35;
    scalefactor = 1/255.0;
    fpsN = 1;


}

yoloDetect::~yoloDetect()
{
    qDebug() << "~yoloDetect()";
    cap.release();
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

    int degree = 0;
    while(true){
        QElapsedTimer time;
        time.start();
        cap.read(m_frame);
        if(degree % fpsN != 0){
            degree++;
            continue;
        }
        if(m_frame.empty()){
            qDebug() << "m_frame is null!";
            break;
        }
        qDebug() <<"cols:"<< m_frame.cols;
        qDebug() <<"rows:" << m_frame.rows;
        if(!boxes.empty() or !confidences.empty()){
            boxes.clear();
            confidences.clear();
        }
        cv::dnn::blobFromImage(m_frame, blob, scalefactor, cv::Size(width, height), cv::Scalar(), true, false);
        net.setInput(blob);
        std::vector<cv::Mat> outs;
        std::vector<std::string> names;
        this->getOutputNames(names);
        net.forward(outs, names);
        std::vector<int> classIds;
        qDebug() << "outs.size:" << outs.size();
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
        qDebug() << "boxes.size::" << boxes.size() << "confidences.size:" << confidences.size();
        qDebug() << m_thread << " " << m_NMSThread;
        std::vector<int> indices;
        cv::dnn::NMSBoxes(boxes, confidences, m_thread, m_NMSThread, indices);
        std::vector<cv::Rect> boxess;
        std::vector<int> classIdss;
        for(auto i:indices){
            int idx = i;
            cv::Rect box = boxes[idx];
            classIdss.push_back(classIds[idx]);
            boxess.push_back(box);
        }
        int milsec = time.elapsed(); //获取片段运行时间
        qDebug() << "推理时间：" << milsec;
        qDebug() << "boxes.size:" << boxess.size();
        qDebug() << "classIds.size:" << classIds.size();
        emit sendBoxes(boxess, classIds, m_frame);
    }
    degree++;
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
    if(!cap.open(m_videoFile.toStdString())){
        qDebug() << "open video faild!!!";
        QMessageBox::warning(nullptr, "ERROR","open video faild!!!",QMessageBox::Yes);
    }else{
        /*
          需要添加异常处理
         */
        qDebug() << "is Open:"<<cap.isOpened();
    }

    m_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    m_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = cap.get(cv::CAP_PROP_FPS);
    qDebug() << "video_w:" << m_width << " " << "video_h:" << m_height;
    qDebug() << "video_fps:" << fps;

}
