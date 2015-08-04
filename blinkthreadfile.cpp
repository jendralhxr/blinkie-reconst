#include "blinkthreadfile.h"
#include <QFileDialog>

#define FPS_SOURCE 10000
#define FPS_VIEW 30

char lum_max, lum_min, lum_current;
char parity;

blinkThreadFile::blinkThreadFile(QThread *parent) : QThread(parent)
{

}

blinkThreadFile::~blinkThreadFile()
{

}

void blinkThreadFile::updatePath(QString setpath){
    path = setpath;
    qDebug("path set to %s",path.toStdString().c_str());
}

void blinkThreadFile::startReading(){
    start(QThread::HighPriority);
}

void blinkThreadFile::setSequenceNumber(int num){
    framecount = num;
    qDebug("framecount set to %d",framecount);
}

void blinkThreadFile::setThreshold(int thres){
    threshold= thres;
    qDebug("threshold set to %d",threshold);
}

void blinkThreadFile::run(){
    value_current= 0;
    value_prev= 0;
    value_temp= 0;
    index_char= 0;
    char state= 0; // 0= waiting for data; 1=just read data, waiting for 0
    for (int framenum=0; framenum<framecount; framenum++){
        filename.sprintf("%s%04d.jpg",path.toStdString().c_str(),framenum);
        image.release();
        tmp.release();
        image = cv::imread(filename.toStdString());
        if(!image.data) qDebug ("%d not found",framenum);
        else {
            // some image parsing here on intersections!!!
            // qDebug("%d open %s",framenum,filename.toStdString().c_str());

            // work on grayscale instead of BGR
            cvtColor(image, tmp, CV_BGR2GRAY);

            //qDebug("%d;%d;%d;%d;%d;%d;%d;%d",\
            // tmp.data[axisY*image.cols + axisX[0]], tmp.data[axisY*image.cols + axisX[1]],\
            // tmp.data[axisY*image.cols + axisX[2]], tmp.data[axisY*image.cols + axisX[3]],\
            // tmp.data[axisY*image.cols + axisX[4]], tmp.data[axisY*image.cols + axisX[5]],\
            // tmp.data[axisY*image.cols + axisX[6]], tmp.data[axisY*image.cols + axisX[7]]\
            // );

            // read current frame's character value
            value_temp= 0;
            lum_max= 0;
            lum_min= 255;
            parity= 0;

            for (char n=0; n<8; n++){
                lum_current = tmp.data[(axisY*image.cols + axisX[n])];
                if (lum_current > lum_max) lum_max= lum_current;
                if (lum_current < lum_min) lum_min= lum_current;
                if ( lum_current> threshold){
                    if (n<7) value_temp |= (1<<n); //7-bit only ascii
                    parity++;
                }
            }

            qDebug("%d;%x;%d;%d;%d;%d",framenum,value_temp,lum_min,lum_max,lum_max-lum_min,parity&1);

            // temporal character being read
//            if (parity&1) qDebug("%d;%c %x: %d %d %d",framenum,value_temp,value_temp,lum_min,lum_max,lum_max-lum_min);
 //           else qDebug("%d reads %c %x: %d %d %d",framenum,value_temp,value_temp,lum_min,lum_max,lum_max-lum_min);

            // render more recent frame
            // 10k fps (source) / 30 fps (viewing) = 304 fps (factor)
            if (!(framenum%30)){
                switch (image.type()) {
                case CV_8UC1:
                    cv::cvtColor(image, tmp, CV_GRAY2RGB);
                    break;
                case CV_8UC3:
                    cv::cvtColor(image, tmp, CV_BGR2RGB);
                    break;
                }
                assert(tmp.isContinuous());
                fresh = QImage(tmp.data, tmp.cols, tmp.rows, tmp.cols*3, QImage::Format_RGB888);
                emit newFrame(fresh);

            }
        }
    }
}

void blinkThreadFile::setAxisY0(int y){
    axisY= y;
}

void blinkThreadFile::setAxisX0(int x){
    axisX[0]= x;
}
void blinkThreadFile::setAxisX1(int x){
    axisX[1]= x;
}
void blinkThreadFile::setAxisX2(int x){
    axisX[2]= x;
}
void blinkThreadFile::setAxisX3(int x){
    axisX[3]= x;
}
void blinkThreadFile::setAxisX4(int x){
    axisX[4]= x;
}
void blinkThreadFile::setAxisX5(int x){
    axisX[5]= x;
}
void blinkThreadFile::setAxisX6(int x){
    axisX[6]= x;
}
void blinkThreadFile::setAxisX7(int x){
    axisX[7]= x;
}
