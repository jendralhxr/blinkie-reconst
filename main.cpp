#include <QApplication>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "blinkdisp.h"
#include "blinkthreadfile.h"

#ifndef IMG_SIZE
#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 48
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSpinBox *spinbox0 =  new QSpinBox();
    QSpinBox *spinbox1 =  new QSpinBox();
    QSpinBox *spinbox2 =  new QSpinBox();
    QSpinBox *spinbox3 =  new QSpinBox();
    QSpinBox *spinbox4 =  new QSpinBox();
    QSpinBox *spinbox5 =  new QSpinBox();
    QSpinBox *spinbox6 =  new QSpinBox();
    QSpinBox *spinbox7 =  new QSpinBox();
    QSpinBox *spinboxY =  new QSpinBox();
    QSpinBox *spinboxSequence = new QSpinBox();
    spinboxSequence->setMaximum(5000);
    QSpinBox *spinboxThreshold = new QSpinBox();
    spinboxThreshold->setMaximum(255);
    spinbox0->setMaximum(IMAGE_WIDTH);
    spinbox1->setMaximum(IMAGE_WIDTH);
    spinbox2->setMaximum(IMAGE_WIDTH);
    spinbox3->setMaximum(IMAGE_WIDTH);
    spinbox4->setMaximum(IMAGE_WIDTH);
    spinbox5->setMaximum(IMAGE_WIDTH);
    spinbox6->setMaximum(IMAGE_WIDTH);
    spinbox7->setMaximum(IMAGE_WIDTH);
    spinboxY->setMaximum(IMAGE_HEIGHT);
    QLabel *labelX = new QLabel("<font color=blue>x positions [7..0]</font>");
    QLabel *labelY = new QLabel("<font color=blue>y position</font>");
    QLabel *labelData = new QLabel("<font color=green>read data</font>");
    QLabel *labelPath = new QLabel("<font color=green>path to images</font>");
    QLabel *labelImage = new QLabel("<font color=green>image</font>");
    QLabel *labelSequence = new QLabel("<font color=green>number of frames</font>");
    QLabel *labelThreshold = new QLabel("<font color=green>luminance threshold</font>");
    QLineEdit *lineData = new QLineEdit("--blank data lingers around here--");
    QLineEdit *linePath = new QLineEdit();
    QPushButton *buttonStart = new QPushButton("start parsing");

    lineData->setReadOnly(true);
    lineData->setMinimumWidth(500);
    linePath->setMinimumWidth(500);

    blinkDisp *sensa =  new blinkDisp();
    blinkThreadFile *tada =  new blinkThreadFile();

    QWidget *viewer = new QWidget();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(  labelX,0,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox7,1,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox6,2,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox5,3,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox4,4,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox3,5,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox2,6,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox1,7,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinbox0,8,0,1,1,Qt::AlignLeft);
    layout->addWidget(  labelY,9,0,1,1,Qt::AlignLeft);
    layout->addWidget(spinboxY,10,0,1,1,Qt::AlignLeft);

    layout->addWidget(labelPath,0,1,1,1,Qt::AlignLeft);
    layout->addWidget(linePath,1,1,1,5,Qt::AlignLeft);
    layout->addWidget(labelSequence,2,1,1,1,Qt::AlignLeft);
    layout->addWidget(spinboxSequence,2,2,1,1,Qt::AlignLeft);
    layout->addWidget(labelThreshold,3,1,1,1,Qt::AlignLeft);
    layout->addWidget(spinboxThreshold,3,2,1,1,Qt::AlignLeft);
    layout->addWidget(buttonStart,4,2,1,1,Qt::AlignLeft);
    layout->addWidget(labelImage,4,1,1,1,Qt::AlignLeft);
    layout->addWidget(sensa,5,1,4,4,Qt::AlignLeft);
    layout->addWidget(labelData,9,1,1,1,Qt::AlignLeft);
    layout->addWidget(lineData,10,1,1,5,Qt::AlignLeft);

    viewer->setLayout(layout);
    viewer->show();

    QObject::connect(spinboxY,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisY0(int)));
    QObject::connect(spinbox0,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX0(int)));
    QObject::connect(spinbox1,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX1(int)));
    QObject::connect(spinbox2,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX2(int)));
    QObject::connect(spinbox3,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX3(int)));
    QObject::connect(spinbox4,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX4(int)));
    QObject::connect(spinbox5,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX5(int)));
    QObject::connect(spinbox6,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX6(int)));
    QObject::connect(spinbox7,SIGNAL(valueChanged(int)),sensa,SLOT(setAxisX7(int)));

    QObject::connect(spinboxY,SIGNAL(valueChanged(int)),tada,SLOT(setAxisY0(int)));
    QObject::connect(spinbox0,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX0(int)));
    QObject::connect(spinbox1,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX1(int)));
    QObject::connect(spinbox2,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX2(int)));
    QObject::connect(spinbox3,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX3(int)));
    QObject::connect(spinbox4,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX4(int)));
    QObject::connect(spinbox5,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX5(int)));
    QObject::connect(spinbox6,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX6(int)));
    QObject::connect(spinbox7,SIGNAL(valueChanged(int)),tada,SLOT(setAxisX7(int)));

    QObject::connect(linePath,SIGNAL(textEdited(QString)),tada,SLOT(updatePath(QString)));
    QObject::connect(buttonStart,SIGNAL(clicked()),tada,SLOT(startReading()));
    QObject::connect(buttonStart,SIGNAL(clicked()),sensa,SLOT(drawOverlay()));
    QObject::connect(spinboxSequence,SIGNAL(valueChanged(int)),tada,SLOT(setSequenceNumber(int)));
    QObject::connect(spinboxThreshold,SIGNAL(valueChanged(int)),tada,SLOT(setThreshold(int)));
    QObject::connect(tada,SIGNAL(newLine(QString)),lineData,SLOT(setText(QString)));
    QObject::connect(tada,SIGNAL(newFrame(QImage)),sensa,SLOT(updateImage(QImage)));

    spinboxY->setValue(20);
    spinbox7->setValue(114);
    spinbox6->setValue(130);
    spinbox5->setValue(145);
    spinbox4->setValue(161);
    spinbox3->setValue(176);
    spinbox2->setValue(191);
    spinbox1->setValue(207);
    spinbox0->setValue(222);
    spinboxSequence->setValue(400);
    spinboxThreshold->setValue(75);

    return a.exec();
}
