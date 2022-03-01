#include "mainWidget.h"
#include "ui_mainWidget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_yoloButton_clicked()
{
    yoloTool *yoloWindows = nullptr;
    if(yoloWindows == nullptr){
        yoloWindows = new yoloTool();
        yoloWindows->show();
    }
    qDebug() << "on_yoloButton_clicked";
}

