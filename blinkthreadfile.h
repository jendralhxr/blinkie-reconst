#ifndef BLINKTHREADFILE_H
#define BLINKTHREADFILE_H

#include <QThread>
#include <QImage>
#include <opencv2/opencv.hpp>

#ifndef IMG_SIZE
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 48
#endif

class blinkThreadFile : public QThread
{
    Q_OBJECT
public:
    explicit blinkThreadFile(QThread *parent = 0);
    ~blinkThreadFile();

signals:
    void newFrame(QImage frame);
    void newLine(QString data);

public slots:
    void setAxisY0(int y);
    void setAxisX0(int x);
    void setAxisX1(int x);
    void setAxisX2(int x);
    void setAxisX3(int x);
    void setAxisX4(int x);
    void setAxisX5(int x);
    void setAxisX6(int x);
    void setAxisX7(int x);
    void startReading();
    void updatePath(QString setpath);
    void setSequenceNumber(int num);
    void setThreshold(int thres);

private:
    void run();
    cv::Mat image, tmp;
    int framecount;
    char value_current, value_prev, value_temp, index_char;
    char buffer[256];
    QString path, filename;
    QImage fresh;
    int axisY;
    int axisX[8];
    int threshold;
    unsigned char lum_max, lum_min, lum_current;

};

#endif // BLINKTHREADFILE_H
