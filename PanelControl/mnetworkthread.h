#ifndef MNETWORKTHREAD_H
#define MNETWORKTHREAD_H
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QLabel>
#include <QUdpSocket>
#include "mallthreads.h"
#include "mnetworksocket.h"
#include "mpanel.h"

class mNetworkThread : public mAllThreads
{
public:
    bool shutdown;
    QMutex* pixelMutex;
    mNetworkThread(QMutex* pixel);
    void run();
    MnetworkSocket* UDPSocket;

public slots:
    void readReady();
};

#endif // MNETWORKTHREAD_H
