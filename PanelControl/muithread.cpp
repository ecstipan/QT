#include "muithread.h"
#include <QtCore>
#include <QDebug>
#include <QPixmap>
#include <QThread>
#include "main.h"
#include "mpanel.h"

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
            //update our panel UI
            MPanel::refreshLocalArrayMap();

            //perform our redraw operation
            updateOverlay();

            /*
            //copy our video image in the BG
            if (globalRawImage.data()->isNull() == false) {
                QImage temp = *globalRawImage.data();
                this->parentWindow->updateRawVideo(temp);
                //qDebug() << "Updating Image";
            } //else qDebug() << "Unable to update GUI";
            */
        this->pixelMutex->unlock();
        msleep(33);
    }
    quit();
}
