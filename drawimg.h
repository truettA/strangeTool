#ifndef DRAWIMG_H
#define DRAWIMG_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

class DrawImg : public QWidget
{
    Q_OBJECT
public:
    explicit DrawImg(QWidget *parent = nullptr);

public:
    //opencv 绘制参数
    int m_fontFace;                 //字体类型
    cv::Point m_org;                //图像中文本字符串的左下角。
    cv::Scalar m_textColor;         //绘制颜色
    cv::Scalar m_rectangleColor;    //绘制方形颜色
    std::string m_text;             //绘制文字内容
    int m_textThickness;            //文本字体粗细
    int m_ractThickness;            // 方框线条粗细
    double m_fontScale;



public:
    void drawBoxs(cv::Mat &frame, std::vector<cv::Rect> &boxes, std::vector<int> &indices, std::vector<float> &confidences);

signals:

};

#endif // DRAWIMG_H
