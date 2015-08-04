#ifndef BLINKDISP_H
#define BLINKDISP_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <opencv2/opencv.hpp>

#ifndef IMG_SIZE
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 96
#endif

class blinkDisp : public QLabel
{
    Q_OBJECT
public:
    explicit blinkDisp(QWidget *parent = 0);
    ~blinkDisp();

signals:

public slots:
    void renderImage();
    void drawOverlay();
    void setAxisY0(int y);
    void setAxisX0(int x);
    void setAxisX1(int x);
    void setAxisX2(int x);
    void setAxisX3(int x);
    void setAxisX4(int x);
    void setAxisX5(int x);
    void setAxisX6(int x);
    void setAxisX7(int x);
    void updateImage(QImage newdisplay);

private:
    cv::Mat image, tmp;
    QImage disp;
    QPainter painter;
    int axisY;
    int axisX[8];
};

#endif // BLINKDISP_H
