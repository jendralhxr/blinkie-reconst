#include "blinkdisp.h"

blinkDisp::blinkDisp(QWidget *parent) : QLabel(parent){
    setMinimumSize(IMAGE_WIDTH,IMAGE_HEIGHT);
    image.release();
    tmp.release();
    image = cv::imread("test.bmp");
    switch (image.type()) {
    case CV_8UC1:
        cv::cvtColor(image, tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cv::cvtColor(image, tmp, CV_BGR2RGB);
        break;
    }
    assert(tmp.isContinuous());
    disp = QImage(tmp.data, tmp.cols, tmp.rows, tmp.cols*3, QImage::Format_RGB888);
    renderImage();
}

blinkDisp::~blinkDisp(){

}

void blinkDisp::renderImage(){
    setPixmap(QPixmap::fromImage(disp));
    update();
}

void blinkDisp::drawOverlay(){
    renderImage();
    QPen pen;
    painter.begin(&disp);
    pen.setWidth(1);
    // draw lines
    pen.setColor(qRgb(0,200,0));
    painter.setPen(pen);
    painter.drawLine(0, axisY, IMAGE_WIDTH-1, axisY);
    pen.setColor(qRgb(200,120,0));
    painter.setPen(pen);
    for (int i=0; i<8; i++){
        painter.drawLine(axisX[i], 0, axisX[i], IMAGE_HEIGHT-1);
    }
    painter.end();
    setPixmap(QPixmap::fromImage(disp));
    update();
}

void blinkDisp::updateImage(QImage newdisplay){
    disp = newdisplay;
    renderImage();
    drawOverlay();
}

void blinkDisp::setAxisY0(int y){
    axisY= y;
    drawOverlay();
}

void blinkDisp::setAxisX0(int x){
    axisX[0]= x;
    drawOverlay();
}
void blinkDisp::setAxisX1(int x){
    axisX[1]= x;
    drawOverlay();
}
void blinkDisp::setAxisX2(int x){
    axisX[2]= x;
    drawOverlay();
}
void blinkDisp::setAxisX3(int x){
    axisX[3]= x;
    drawOverlay();
}
void blinkDisp::setAxisX4(int x){
    axisX[4]= x;
    drawOverlay();
}
void blinkDisp::setAxisX5(int x){
    axisX[5]= x;
    drawOverlay();
}
void blinkDisp::setAxisX6(int x){
    axisX[6]= x;
    drawOverlay();
}
void blinkDisp::setAxisX7(int x){
    axisX[7]= x;
    drawOverlay();
}
