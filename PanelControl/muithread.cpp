#include "muithread.h"
#include <QtCore>
#include <QDebug>
#include <QPixmap>
#include <QThread>

mUIThread::mUIThread(QMutex *pixel)
{
    pixelMutex = pixel;
    shutdown = false;
}

void mUIThread::run()
{
    shutdown = false;

    while (!shutdown) {
        this->pixelMutex->lock();
            if (globalRawImage.data()->isNull() == false && parentWindow->isDisplayingVideo == true) {
                QImage temp = *globalRawImage.data();
                this->parentWindow->updateRawVideo(temp);
                //qDebug() << "Updating Image";
            } //else qDebug() << "Unable to update GUI";
        this->pixelMutex->unlock();
        msleep(33);
    }
    quit();
}
