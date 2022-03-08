#include "rwfile.h"

RWFile::RWFile()
{

}

RWFile::RWFile(QString savePath, QString fileName)
{
    m_savePath = savePath;
    m_fileName = fileName;
}

void RWFile::readClassFile(QString classesFile, QVector<QString> &classes)
{

}

void RWFile::writeText(std::vector<cv::Rect> &boxes, int cols, int rows)
{
    QFile file(m_savePath + m_fileName);
    for(cv::Rect box: boxes){
        if(file.open(QIODevice::WriteOnly)){
            float num1_x = (box.x + box.width/2.0)/ cols;
            float num2_y = (box.y + box.height/2.0)/ rows;
            float num3_w = box.width / (float)cols;
            float num4_h = box.height / (float)rows;
            int num0_class = 1;     //需要添加
            char buf[128] = { 0 };
            sprintf(buf, "%d %07.6f %07.6f %07.6f %07.6f\n",num0_class, num1_x, num2_y, num3_w, num4_h);
            file.write(buf);
        }
    }
    file.close();
}

void RWFile::recvBoxes(std::vector<cv::Rect> boxes, cv::Mat frame)
{
    writeText(boxes, frame.cols, frame.rows);
}

