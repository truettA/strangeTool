#include "rwfile.h"
#include <QDebug>
#include <QThread>
#include <QTime>

RWFile::RWFile(QObject *parent):QObject(parent)
{
    numTmp = 0;
}

RWFile::RWFile(QString savePath, QString fileName,QObject *parent):QObject(parent)
{
    m_savePath = savePath;
    m_fileName = fileName;
    numTmp = 0;
}

void RWFile::readClassFile(QString classesFile, QVector<QString> &classes)
{

}

void RWFile::writeText(std::vector<cv::Rect> &boxes, std::vector<int> classIds, cv::Mat frame)
{

    char cTmp[10] = {0};
    sprintf(cTmp, "%07d", numTmp);

    if(isSaveTxt){
        QFile file(m_savePath + "/" + m_fileName + cTmp +".txt");
        for(cv::Rect box: boxes){
            int i = 0;
            if(file.open(QIODevice::WriteOnly)){
                float num1_x = (box.x + box.width/2.0)/ frame.cols;
                float num2_y = (box.y + box.height/2.0)/ frame.rows;
                float num3_w = box.width / (float)frame.cols;
                float num4_h = box.height / (float)frame.rows;
                int num0_class = classIds[i];     //需要添加
                i++;
                char buf[128] = { 0 };
                sprintf(buf, "%d %07.6f %07.6f %07.6f %07.6f\n",num0_class, num1_x, num2_y, num3_w, num4_h);
                qDebug() <<"buf: " <<buf;
                file.write(buf);

            }
        }
        file.close();
    }
    if(isSaveImg){
        //cv::imwrite((m_savePath + m_fileName + ".jpg").toStdString(), frame);
    }
    numTmp++;
}

void RWFile::recvBoxes(std::vector<cv::Rect> boxes, std::vector<int> classIds, cv::Mat frame)
{
    qDebug() << "RWfile==========";
    qDebug() << "rwfile thread:" << QThread::currentThread();
    writeText(boxes, classIds, frame);
}

