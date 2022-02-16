#include "yolotool.h"
#include "ui_yolotool.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <yolodetect.h>


yoloTool::yoloTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yoloTool)
{
    ui->setupUi(this);
    ui->rcpuButton->setChecked(true);


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
    if(ui->rcpuButton->isChecked()){
        qDebug() <<"rcup";
    }else if(ui->rgpuButton->isChecked()){
        qDebug() << "rgup";
    }
    qDebug() << ui->cfgEdit->text();
    qDebug() << ui->weightEdit->text();
    cv::destroyWindow("show");
}


void yoloTool::on_startDectButton_clicked()
{
    /*
    * List of supported combinations backend / target:
    * |                        | DNN_BACKEND_OPENCV | DNN_BACKEND_INFERENCE_ENGINE | DNN_BACKEND_HALIDE |  DNN_BACKEND_CUDA |
    * |------------------------|--------------------|------------------------------|--------------------|-------------------|
    * | DNN_TARGET_CPU         |                  + |                            + |                  + |                   |
    * | DNN_TARGET_OPENCL      |                  + |                            + |                  + |                   |
    * | DNN_TARGET_OPENCL_FP16 |                  + |                            + |                    |                   |
    * | DNN_TARGET_MYRIAD      |                    |                            + |                    |                   |
    * | DNN_TARGET_FPGA        |                    |                            + |                    |                   |
    * | DNN_TARGET_CUDA        |                    |                              |                    |                 + |
    * | DNN_TARGET_CUDA_FP16   |                    |                              |                    |                 + |
    */

    yoloDetect detect = yoloDetect();
    if(ui->rcpuButton->isChecked()){
        detect.backendId = cv::dnn::DNN_BACKEND_OPENCV;
        detect.targetId = cv::dnn::DNN_TARGET_CPU;
    }else if(ui->rgpuButton->isChecked()){
        detect.backendId = cv::dnn::DNN_BACKEND_CUDA;
        detect.targetId = cv::dnn::DNN_TARGET_CUDA;
    }
    detect.m_modelCfg = ui->cfgEdit->text();
    detect.m_weightsFile = ui->weightEdit->text();

}


void yoloTool::on_rcpuButton_clicked()
{
    qDebug() << "cup";
}


void yoloTool::on_rgpuButton_clicked()
{
    qDebug() << "gpu";
}

