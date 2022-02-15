#include "yolotool.h"
#include "ui_yolotool.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

yoloTool::yoloTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yoloTool)
{
    ui->setupUi(this);

    cv::Mat frame = cv::imread("/Users/tangtang/Desktop/桌面壁纸/315955-106.jpg");
    cv::imshow("show", frame);

}

yoloTool::~yoloTool()
{
    delete ui;
    qDebug() << "yoloWindows destroy";
}

void yoloTool::closeEvent(QCloseEvent *event)
{
    delete this;
    qDebug() << "yoloWindows closeEvent";
}

void yoloTool::on_closeShowButton_clicked()
{
    cv::destroyWindow("show");
}

