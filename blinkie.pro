######################################################################
# Automatically generated by qmake (2.01a) Wed May 20 17:20:23 2015
######################################################################

TEMPLATE = app
TARGET = test
INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/lib64 \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui
#-lopencv_ml \
#-lopencv_video \
#-lopencv_features2d \
#-lopencv_calib3d \
#-lopencv_objdetect \
#-lopencv_contrib \
#-lopencv_legacy \
#-lopencv_flann

# Input
HEADERS += blinkdisp.h blinkthreadfile.h
SOURCES += blinkdisp.cpp blinkthreadfile.cpp main.cpp