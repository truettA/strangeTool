#ifndef YOLOTOOL_H
#define YOLOTOOL_H

#include <QWidget>
#include <QEvent>
#include "yolodetect.h"
#include "drawimg.h"
#include "rwfile.h"

namespace Ui {
class yoloTool;
}

class yoloTool : public QWidget
{
    Q_OBJECT

public:
    explicit yoloTool(QWidget *parent = nullptr);
    ~yoloTool();

public:
    DrawImg *drawImg;

private:
    Ui::yoloTool *ui;

    yoloDetect *detect;
    RWFile *rwFile;
private slots:
    void closeEvent(QCloseEvent *event);


    void on_closeShowButton_clicked();
    void on_startDectButton_clicked();
    void on_rcpuButton_clicked();
    void on_rgpuButton_clicked();
    void on_selectPictureButton_clicked();
    void on_selectCfgBtn_clicked();
    void on_selectVideoButton_clicked();
    void on_saveBtn_clicked();

public slots:
    void recvBoxes(std::vector<cv::Rect> boxes, std::vector<int> classIds, cv::Mat frame);
//    void sendWorking(std::vector<cv::Rect> boxes);
};

#endif // YOLOTOOL_H
