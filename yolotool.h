#ifndef YOLOTOOL_H
#define YOLOTOOL_H

#include <QWidget>
#include <QEvent>
#include "yolodetect.h"

namespace Ui {
class yoloTool;
}

class yoloTool : public QWidget
{
    Q_OBJECT

public:
    explicit yoloTool(QWidget *parent = nullptr);
    ~yoloTool();

private:
    Ui::yoloTool *ui;

    QThread *qThread;
    yoloDetect *detect;
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
    void recvBoxes(std::vector<cv::Rect> boxes);
};

#endif // YOLOTOOL_H
