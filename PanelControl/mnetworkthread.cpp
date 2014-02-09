#include "main.h"
#include "mnetworkthread.h"
#include <QtCore>
#include <QDebug>
#include <QUdpSocket>

mNetworkThread::mNetworkThread(QMutex *pixel)
{
    pixelMutex = pixel;
    shutdown = false;
}

void mNetworkThread::run()
{
    shutdown = false;
    while (!shutdown) {
        this->pixelMutex->lock();
        //process video data
        //perform any other panel handling stuff

        //check for timeouts

        this->pixelMutex->unlock();
        msleep(1000);
    }
    quit();
}
