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
#include "main.h"

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
MPanel *_globalPanels[122][122];
cv::VideoCapture videoInput;
unsigned short int cameraNumber = 0;
unsigned int cameraWidth = 1920;
unsigned int cameraHeight = 1080;
unsigned int cameraFPS = 25;

//setup voletile shared memory
QMutex _PixelAccess;

//Setup our Main Window
MainWindow *mainWindowPointer;
mAllThreads _VideoThread;

void updateOverlay()
{
    if (mainWindowPointer != NULL)
        mainWindowPointer->updateArrayOverlay();
}

void logConsole(QString temp)
{
    if (mainWindowPointer != NULL)
        mainWindowPointer->addConsoleLogEvent(temp);
}

void selectCamera(int cam) {
    cameraNumber = cam;
    openCamera();
}

void openCamera() {
    //clear our old video input
    qDebug() << "Opening camera " << cameraNumber;
    logConsole(QString("Initializing Camera Interface..."));
    _PixelAccess.lock();
    if (videoInput.isOpened()) videoInput.release();

    videoInput.set(CV_CAP_PROP_FRAME_WIDTH, cameraWidth);
    videoInput.set(CV_CAP_PROP_FRAME_HEIGHT, cameraHeight);
    videoInput.set(CV_CAP_PROP_FPS, cameraFPS);
    videoInput.open(cameraNumber);
    if(videoInput.isOpened() == false) {
        qWarning("Unable to open device!");
        logConsole(QString("Unable to open device!"));
    }
    videoInput.set(CV_CAP_PROP_FRAME_WIDTH, cameraWidth);
    videoInput.set(CV_CAP_PROP_FRAME_HEIGHT, cameraHeight);
    videoInput.set(CV_CAP_PROP_FPS, cameraFPS);

    mainWindowPointer->isDisplayingVideo = true;
    _PixelAccess.unlock();
}

void closeCamera(){
    _PixelAccess.lock();
    if (videoInput.isOpened()) videoInput.release();
    mainWindowPointer->isDisplayingVideo = false;
    _PixelAccess.unlock();
}

void setResolution(int index){
    qDebug() << "Setting resolution to index " << index;
    if (index == 0) {
        cameraWidth = 1920;
        cameraHeight = 1080;
    } else if (index == 1) {
        cameraWidth = 1600;
        cameraHeight = 900;
    } else if (index == 2) {
        cameraWidth = 1280;
        cameraHeight = 720;
    } else if (index == 3) {
        cameraWidth = 960;
        cameraHeight = 540;
    } else if (index == 4) {
        cameraWidth = 640;
        cameraHeight = 360;
    }
    _VideoThread.cameraW = cameraWidth;
    _VideoThread.cameraH = cameraHeight;
    mainWindowPointer->cameraW = cameraWidth;
    mainWindowPointer->cameraH = cameraHeight;
}

void setFPS(int index){
    if (index == 0) {
        cameraFPS = 30;
    } else if (index == 1){
        cameraFPS = 25;
    } else if (index == 2){
        cameraFPS = 24;
    } else if (index == 3){
        cameraFPS = 10;
    } else if (index == 4){
        cameraFPS = 5;
    } else if (index == 51){
        cameraFPS = 1;
        _VideoThread.cameraFPS = 1;
    }
    _VideoThread.cameraFPS = cameraFPS;
    mainWindowPointer->cameraFPS = cameraFPS;
}

int main(int argc, char *argv[])
{
    QApplication::setStyle("plastique");
    QApplication a(argc, argv);

    MainWindow windowHome;
    mainWindowPointer = &windowHome;

    logConsole(QString("Initializing Camera Interface..."));

    int i;
    for (i=0; i<10; i++) {
        videoInput.open(i);
        if (videoInput.isOpened()== false){
            break;
        } else {
            windowHome.addCameraToSelector();
        }
    }

    //Shared between multiple threads
    QSharedPointer<QImage> rawVideoInput = QSharedPointer<QImage>(new QImage);
    QSharedPointer<QImage> processedVideoInput = QSharedPointer<QImage>(new QImage);

    //Initialize Threads
    mVideoThread    _VideoThread(&_PixelAccess);           //Handles Video Processing
                                            //Dumps data over UDP

    mNetworkThread  _NetworkUpdateThread(&_PixelAccess);   //Handles Panel and Array Mapping

    mUIThread       _UIThread(&_PixelAccess);              //Handles UI and Lower Priority Tasks


    //Assign Pointers
    windowHome.thread1 = &_VideoThread;
    windowHome.thread2 = &_NetworkUpdateThread;
    windowHome.thread3 = &_UIThread;
    windowHome.mutex = &_PixelAccess;

    //Initialize Other things
    _VideoThread.cameraObject = &videoInput;
    _VideoThread.globalRawImage = rawVideoInput;
    _VideoThread.globalProcessedImage = processedVideoInput;
    _VideoThread.cameraFPS = 25;

    _UIThread.parentWindow = &windowHome;
    _UIThread.globalRawImage = rawVideoInput;
    _UIThread.globalProcessedImage = processedVideoInput;

    logConsole(QString("Initializing threads... "));
    //Start our Threads
    _VideoThread.start(QThread::NormalPriority);
    _NetworkUpdateThread.start(QThread::NormalPriority);
    _UIThread.start(QThread::LowPriority);

    //Finally ready to display something
    windowHome.show();

    //Let's do some test initialization
    if (MPanel::addPanel(61,61)) qDebug() << "Added panel!";
    if (MPanel::addPanel(60,61)) qDebug() << "Added panel!";
    if (MPanel::addPanel(61,59)) qDebug() << "Added panel!";
    if (MPanel::addPanel(62,59)) qDebug() << "Added panel!";
    if (MPanel::addPanel(63,59)) qDebug() << "Added panel!";
    //MPanel::getPanelAtLocation(63,59)->setState(DISPLAY_ERROR);
    if (MPanel::addPanel(59,61)) qDebug() << "Added panel!";
    MPanel::getPanelAtLocation(59,61)->setState(DISPLAY_ERROR);
    if (MPanel::addPanel(61,60)) qDebug() << "Added panel!";
    if (MPanel::addPanel(59,62)) qDebug() << "Added panel!";

    if (MPanel::panelExistsAt(61,61)) qDebug() << "Found Panel!";
        else qDebug() << "Did not find Panel!";

    //Let's get the ball rolling...
    return a.exec();
}
