#include "muithread.h"
#include <QtCore>
#include <QDebug>
#include <QPixmap>

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
            if (globalProcessedImage.data()->isNull() == false) {
                QImage temp = *globalProcessedImage.data();
                this->parentWindow->updateRawVideo(temp);
                //qDebug() << "Updating Image";
            } //else qDebug() << "Unable to update GUI";
        this->pixelMutex->unlock();
        usleep(30);
    }
    quit();
}
