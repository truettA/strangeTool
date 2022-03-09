#ifndef RWFILE_H
#define RWFILE_H
#include <QString>
#include <QFile>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


class RWFile:public QObject
{
    Q_OBJECT
public:
    RWFile(QObject *parent = nullptr);
    RWFile(QString savePath, QString fileName,QObject *parent = nullptr);
public:
    QString m_fileName;
    QString m_savePath;
    bool isSaveTxt;
    bool isSaveImg;

private:
    int numTmp;

public:
    static void readClassFile(QString classesFile, QVector<QString> &classes);

public:
    void writeText(std::vector<cv::Rect> &boxes, std::vector<int> classIds, cv::Mat frame);

public slots:
    void recvBoxes(std::vector<cv::Rect> boxes, std::vector<int> classIds, cv::Mat frame);
};

#endif // RWFILE_H
