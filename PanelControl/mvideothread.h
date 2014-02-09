#ifndef MVIDEOTHREAD_H
#define MVIDEOTHREAD_H
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mallthreads.h"
#include "mainwindow.h"

class mVideoThread : public mAllThreads
{
public:
    cv::VideoCapture* cameraObject;
    cv::Mat matRawInput;
    cv::Mat matProcessedInput;
    QSharedPointer<QImage> globalRawImage;
    QSharedPointer<QImage> globalProcessedImage;
    MainWindow* parentWindow;
    bool shutdown;
    unsigned int cameraFPS;
    unsigned int cameraW;
    unsigned int cameraH;

    int *uiHandleLeft;
    int *uiHandleRight;
    int *uiHandleBottom;
    int *uiHandleTop;
    int *testPattern;

    QMutex* pixelMutex;
    mVideoThread(QMutex *pixel);
    void run();
public slots:
    void updateHandleLeft(int x);
};



#endif // MVIDEOTHREAD_H
