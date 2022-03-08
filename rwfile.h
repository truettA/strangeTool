#ifndef RWFILE_H
#define RWFILE_H
#include <QString>
#include <QFile>
#include <opencv2/opencv.hpp>


class RWFile
{
public:
    RWFile();
    RWFile(QString savePath, QString fileName);
public:

    QString m_fileName;
    QString m_savePath;

public:
    static void readClassFile(QString classesFile, QVector<QString> &classes);

public:
    void writeText(std::vector<cv::Rect> &boxes, int cols, int rows);

public slots:
    void recvBoxes(std::vector<cv::Rect> boxes, cv::Mat frame);
};

#endif // RWFILE_H
