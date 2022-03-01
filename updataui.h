#ifndef UPDATAUI_H
#define UPDATAUI_H

#include <QObject>
#include <QStringList>
#include "yolotool.h"

class UpdataUI : public QObject
{
    Q_OBJECT
public:
    explicit UpdataUI(QObject *parent = nullptr);

public slots:
    void updataTextLable(QString text);
    void updateTextLable(QStringList textList);

signals:
    void operate(const int);
    void operate(QStringList);
};

#endif // UPDATAUI_H
