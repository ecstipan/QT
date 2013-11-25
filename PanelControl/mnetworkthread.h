#ifndef MNETWORKTHREAD_H
#define MNETWORKTHREAD_H
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QLabel>
#include "mallthreads.h"

class mNetworkThread : public mAllThreads
{
public:
    bool shutdown;
    QMutex* pixelMutex;
    mNetworkThread(QMutex* pixel);
    void run();
};

#endif // MNETWORKTHREAD_H
