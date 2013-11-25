/*=================================
 *
 *
 *  MODULAR LED DISPLAY MQP
 *
 *  Rayce Stipanovich
 *
 *===============================*/

#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>

//OpenCV MQP Headers
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//Custom Classes
#include "mpanelstatus.h"
#include "mpanel.h"

#include "mallthreads.h"
#include "mvideothread.h"
#include "mnetworkthread.h"
#include "muithread.h"

#include "mainwindow.h"
#include <QSharedData>
#include <QSharedDataPointer>
#include <QApplication>

//Define things for globally allocated memory
MPanel **_globalPanels[121][121];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //setup voletile shared memory
    QMutex _PixelAccess;
    cv::VideoCapture videoInput;

    //Shared between multiple threads
    QSharedPointer<QImage> rawVideoInput = QSharedPointer<QImage>(new QImage);
    QSharedPointer<QImage> processedVideoInput = QSharedPointer<QImage>(new QImage);

    //Initialize Threads
    mVideoThread    _VideoThread(&_PixelAccess);           //Handles Video Processing
                                            //Dumps data over UDP

    mNetworkThread  _NetworkUpdateThread(&_PixelAccess);   //Handles Panel and Array Mapping

    mUIThread       _UIThread(&_PixelAccess);              //Handles UI and Lower Priority Tasks

    //Setup our Main Window
    MainWindow windowHome;
    //Assign Pointers
    windowHome.thread1 = &_VideoThread;
    windowHome.thread2 = &_NetworkUpdateThread;
    windowHome.thread3 = &_UIThread;

    //Initialize Other things
    videoInput.open(0);
    if(videoInput.isOpened() == false) {
        qWarning("Unable to open device!");
        return 0;
    }
    videoInput.set(CV_CAP_PROP_FRAME_WIDTH, 1280.0);
    videoInput.set(CV_CAP_PROP_FRAME_HEIGHT, 720.0);

    _VideoThread.cameraObject = &videoInput;
    _VideoThread.globalRawImage = rawVideoInput;
    _VideoThread.globalProcessedImage = processedVideoInput;

    _UIThread.parentWindow = &windowHome;
    _UIThread.globalRawImage = rawVideoInput;
    _UIThread.globalProcessedImage = processedVideoInput;

    //Start our Threads
    _VideoThread.start(QThread::NormalPriority);
    //_NetworkUpdateThread.start(QThread::NormalPriority);
    _UIThread.start(QThread::LowPriority);


    //Finally ready to display something
    windowHome.show();

    //Let's get the ball rolling...
    return a.exec();
}
