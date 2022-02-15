#ifndef YOLOTOOL_H
#define YOLOTOOL_H

#include <QWidget>
#include <QEvent>

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
private slots:
    void closeEvent(QCloseEvent *event);


    void on_closeShowButton_clicked();
};

#endif // YOLOTOOL_H
