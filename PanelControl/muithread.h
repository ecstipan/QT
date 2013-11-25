#ifndef MUITHREAD_H
#define MUITHREAD_H
#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QLabel>
#include <QImage>
#include "mallthreads.h"
#include "mainwindow.h"


class mUIThread : public mAllThreads
{
public:
    bool shutdown;
    QMutex* pixelMutex;
    QSharedPointer<QImage> globalRawImage;
    QSharedPointer<QImage> globalProcessedImage;

    MainWindow* parentWindow;

    mUIThread(QMutex* pixel);
    void run();
};

#endif // MUITHREAD_H
