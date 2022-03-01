#include "updataui.h"
#include <QThread>
#include <QDebug>

UpdataUI::UpdataUI(QObject *parent)
    : QObject{parent}
{
       connect(this, static_cast<void (UpdataUI::*)(QStringList)>(&UpdataUI::operate), this, static_cast<void (UpdataUI::*)(QStringList)>(&UpdataUI::updateTextLable));
}

void UpdataUI::updataTextLable(QString text)
{

}

void UpdataUI::updateTextLable(QStringList textList)
{
    qDebug() << QThread::currentThread();
    qDebug() << textList;

}


