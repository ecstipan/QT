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
        if (this->UDPSocket->isConnected())
        {
            this->pixelMutex->lock();
            //see if we should wait to rebroadcast
            if (MPanel::getArrayCount() == 0) beginReaddressProcess();

            //check for timeouts

            this->pixelMutex->unlock();
        }
        msleep(1000);
    }
    quit();
}
