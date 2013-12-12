#ifndef MQPAPPLICATION_H
#define MQPAPPLICATION_H
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include "mallthreads.h"
#include <QApplication>


class MQPApplication : public QApplication
{
    Q_OBJECT
public:
    MQPApplication();
    ~MQPApplication();
    mAllThreads* thread1;
    mAllThreads* thread2;
    mAllThreads* thread3;
    QMutex* mutex;
signals:

public slots:

};

#endif // MQPAPPLICATION_H
