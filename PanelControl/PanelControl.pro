#-------------------------------------------------
#
# Project created by QtCreator 2013-11-19T10:19:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PanelControl
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mpanel.cpp \
    mpanelstatus.cpp \
    mvideothread.cpp \
    mnetworkthread.cpp \
    muithread.cpp \
    mallthreads.cpp

HEADERS  += mainwindow.h \
    mpanel.h \
    mpanelstatus.h \
    mvideothread.h \
    mnetworkthread.h \
    muithread.h \
    mallthreads.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:/OpenCV/build/install/include/opencv2
INCLUDEPATH += D:/OpenCV/build/install/include

LIBS += -LD:\\OpenCV\\build\\bin \
    libopencv_core247 \
    libopencv_highgui247 \
    libopencv_imgproc247 \
    libopencv_features2d247 \
    libopencv_calib3d247 \

OTHER_FILES += \
    img.jpg
