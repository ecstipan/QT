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
        this->msleep(300);
        QThread::msleep(300);
    }
    quit();
}
