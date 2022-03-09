#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <QThread>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QValidator>
#include "yolotool.h"
#include "ui_yolotool.h"
#include "yolodetect.h"


yoloTool::yoloTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yoloTool)
{
    ui->setupUi(this);
    ui->rcpuButton->setChecked(true);
    qRegisterMetaType<cv::Rect>("cv::Rect");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<std::vector<cv::Rect>>("std::vector<cv::Rect>");
    qRegisterMetaType<std::vector<int>>("std::vector<int>");

    //限制label输入
    QDoubleValidator *qDoubleValidator = new QDoubleValidator(0, 1, 5, this);
    QIntValidator *qIntValidator = new QIntValidator(1, 100, this);
    ui->nmsTdEdit->setValidator(qDoubleValidator);
    ui->threadEdit->setValidator(qDoubleValidator);
    ui->scalefrEdit->setValidator(qDoubleValidator);
    ui->fpsN->setValidator(qIntValidator);


    // or
    //Q_DECLARE_METATYPE(std::vector<cv::Rect);
    detect = nullptr;
    drawImg = new DrawImg();
    rwFile = new RWFile();
    QThread *frawImgWork = new QThread();
    QThread *fileWork = new QThread();
    drawImg->moveToThread(frawImgWork);
    frawImgWork->start();
    rwFile->moveToThread(fileWork);
    fileWork->start();
    connect(frawImgWork, &QThread::finished, this, [=](){
        qDebug() <<"frawImgWork finished" << QThread::currentThread();
        frawImgWork->destroyed();
    });
    connect(fileWork, &QThread::finished, this, [=](){
        qDebug() <<"fileWork finished" << QThread::currentThread();
        fileWork->destroyed();
    });

}

yoloTool::~yoloTool()
{
    delete ui;
    qDebug() << "yoloWindows destroy";
}

void yoloTool::closeEvent(QCloseEvent *event)
{
    this->destroy();
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
   qDebug() << "开始检测";
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
    QStringList cfgFileL;
    if(fileDialog->exec() == QDialog::Accepted){
        cfgFileL = fileDialog->selectedFiles();
    }
    if(!cfgFileL.isEmpty()){
        for(auto cfgFile:cfgFileL){
            if(cfgFile.lastIndexOf(".cfg") != -1){
                ui->cfgEdit->setText(cfgFile);
            }else if(cfgFile.lastIndexOf(".weights") != -1){
                ui->weightEdit->setText(cfgFile);
            }else if(cfgFile.lastIndexOf(".txt") != -1){
                ui->classesFileEdt->setText(cfgFile);
            }
        }
    }
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
    QStringList tmpList = ui->videoFileEdit->text().split('/');
    QString videoSrcName = tmpList.last();
//    rwFile->m_fileName = videoSrcName.split(".")[0];
    fileDialog->destroyed();

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

    detect = new yoloDetect(videoFile,cfgFile,weight,classesFile);
    if(!ui->threadEdit->text().isEmpty()){
        detect->m_thread = ui->threadEdit->text().toDouble();
        detect->m_NMSThread = ui->nmsTdEdit->text().toDouble();
        detect->scalefactor = ui->scalefrEdit->text().toDouble();
        detect->fpsN = ui->fpsN->text().toInt();
    }
//    if(!ui->saveEdit->text().isEmpty()){
//        rwFile->m_savePath = ui->saveEdit->text();
//    }else{
//        rwFile->m_savePath = "./save";
//    }

    connect(ui->startDectButton, &QPushButton::clicked, detect, &yoloDetect::detctImg);
//    connect(detect, &yoloDetect::sendBoxes, rwFile, &RWFile::recvBoxes);
    connect(detect, &yoloDetect::sendBoxes, drawImg, &DrawImg::recvBoxes);
    connect(detect, &yoloDetect::sendBoxes, this, &yoloTool::recvBoxes);

    if(ui->rcpuButton->isChecked()){
        detect->backendId = cv::dnn::DNN_BACKEND_OPENCV;
        detect->targetId = cv::dnn::DNN_TARGET_CPU;
    }else if(ui->rgpuButton->isChecked()){
        detect->backendId = cv::dnn::DNN_BACKEND_CUDA;
        detect->targetId = cv::dnn::DNN_TARGET_CUDA;
    }
    QThread *qThread = new QThread();
    detect->moveToThread(qThread);

    detect->init();
    qThread->start();

    connect(qThread, &QThread::started, detect, [=](){
        qDebug() <<"started" <<QThread::currentThread();
    });
    connect(qThread, &QThread::finished, this, [=](){
        qDebug() <<"finished" <<QThread::currentThread();
        qThread->destroyed();
    });
}


void yoloTool::on_saveBtn_clicked()
{
    QString savePath = QFileDialog::getExistingDirectory();
    if(!savePath.isEmpty()){
        ui->saveEdit->setText(savePath);
    }

}
void yoloTool::recvBoxes(std::vector<cv::Rect> boxes, std::vector<int> classIds, cv::Mat frame)
{
    qDebug() <<"yrecv=============";
    cv::Mat cloneFrame = frame;

    for(auto box:boxes){
        QString textBox = "x:" + QString::number(box.x) + " y:" + QString::number(box.y) + " width:" + QString::number(box.width) + "height:" + QString::number(box.height) + '\n';
        cv::rectangle(cloneFrame, cv::Point(box.x, box.y), cv::Point(box.x+box.width, box.y+box.height), cv::Scalar(255, 178, 50), 3);
        ui->boxesBrowser->insertPlainText(textBox);
    }
    QPixmap qPixmap = QPixmap::fromImage(drawImg->qImage);
    if(!qPixmap.isNull()){
        ui->imgLabel->setPixmap(qPixmap.scaled(ui->imgLabel->size(), Qt::KeepAspectRatio));
    }
//     cv::imshow("show", cloneFrame);
}

