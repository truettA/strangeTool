#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <QThread>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "updataui.h"
#include "yolotool.h"
#include "ui_yolotool.h"
#include "yolodetect.h"


yoloTool::yoloTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yoloTool)
{
    ui->setupUi(this);
    ui->rcpuButton->setChecked(true);
    qRegisterMetaType<std::vector<cv::Rect>>("std::vector<cv::Rect>");
    // or
    //Q_DECLARE_METATYPE(std::vector<cv::Rect);
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
    qDebug() << "master thread:" << QThread::currentThread();
    QString weight = ui->weightEdit->text();
    if(weight.isEmpty()){
        qDebug() << "weightFile is null!";
    }
    QString cfgFile = ui->cfgEdit->text();
    if(cfgFile.isEmpty()){
        qDebug() << "cfgFile is null!";
    }
    QString classesFile = ui->classesFileEdt->text();
    if(classesFile.isEmpty()){
        qDebug() << "classesFile is null!";
    }
    QString videoFile = ui->videoFileEdit->text();

    detect = new yoloDetect(videoFile,cfgFile,weight,classesFile,ui->threadEdit->text().toDouble());
    connect(detect, &yoloDetect::sendBoxes, this, &yoloTool::recvBoxes);
//    connect(detect, &yoloDetect::sendBoxes, nullptr, [](){});

    if(ui->rcpuButton->isChecked()){
        detect->backendId = cv::dnn::DNN_BACKEND_OPENCV;
        detect->targetId = cv::dnn::DNN_TARGET_CPU;
    }else if(ui->rgpuButton->isChecked()){
        detect->backendId = cv::dnn::DNN_BACKEND_CUDA;
        detect->targetId = cv::dnn::DNN_TARGET_CUDA;
    }
    qThread = new QThread();
    detect->moveToThread(qThread);

    qThread->start();
    detect->init();

//    connect(ui->, &QPushButton::clicked, detect, &yoloDetect::detctImg);


    connect(qThread, &QThread::started, detect, [=](){
        qDebug() <<"started" <<QThread::currentThread();
    });
    connect(qThread, &QThread::finished, this, [=](){
        qDebug() <<"finished" <<QThread::currentThread();
    });


}

void yoloTool::on_rcpuButton_clicked()
{
    qDebug() << "cup";
}

void yoloTool::on_rgpuButton_clicked()
{
    qDebug() << "gpu";
}

void yoloTool::on_selectPictureButton_clicked()
{

}

void yoloTool::on_selectCfgBtn_clicked()
{

    qDebug() << "on_selectCfgBtn_clicked" << ";;; " << QThread::currentThread();
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择权重和配置文件");
    QStringList filtersName;
    filtersName << "(*.cfg *.weights *.txt)"
                << "any file(*)";
    fileDialog->setNameFilters(filtersName);
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    QStringList cfgFile;
    if(fileDialog->exec() == QDialog::Accepted){
        qDebug() << "exec:";
        cfgFile = fileDialog->selectedFiles();
    }

    //需要修改判断
    if(!cfgFile.isEmpty()){
        ui->cfgEdit->setText(cfgFile.at(0));
        ui->weightEdit->setText(cfgFile.at(1));
        ui->classesFileEdt->setText(cfgFile[2]);
    }

//    QThread *thread = new QThread();
//    UpdataUI *updataUi = new UpdataUI();
//    updataUi->moveToThread(thread);
//    connect(thread, &QThread::finished, updataUi, &QObject::deleteLater);//该线程结束时销毁
//    thread->start();
//    updataUi->operate(cfgFile);

    fileDialog->destroyed();
}


void yoloTool::on_selectVideoButton_clicked()
{
    qDebug() << "选择视频文件";
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择权重和配置文件");
    QStringList filtersName;
    filtersName << "(*.mp4 *.avi *.flv)"
                << "any file(*)";
    fileDialog->setNameFilters(filtersName);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory(".");
    QStringList videoFilePath;
    if(fileDialog->exec() == QDialog::Accepted){
       videoFilePath = fileDialog->selectedFiles();
    }
    if(!videoFilePath.isEmpty()){
        ui->videoFileEdit->setText(videoFilePath[0]);
    }
    fileDialog->destroyed();
}


void yoloTool::on_saveBtn_clicked()
{
    QString savePath = QFileDialog::getExistingDirectory();
    if(!savePath.isEmpty()){
        ui->saveEdit->setText(savePath);
    }

}
void yoloTool::recvBoxes(std::vector<cv::Rect> boxes)
{

}

