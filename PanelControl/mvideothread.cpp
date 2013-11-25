#include "mvideothread.h"
#include <QtCore>
#include <QDebug>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QSharedData>
#include <QSharedDataPointer>

mVideoThread::mVideoThread(QMutex* pixel)
{
    pixelMutex = pixel;
    shutdown = false;
}

void mVideoThread::run()
{
    shutdown = false;

    while (!shutdown) {
        this->pixelMutex->lock();
        this->cameraObject->read(matRawInput);
        if (matRawInput.empty() == false) {
            //Do some blur processing...
            cv::GaussianBlur(this->matRawInput, this->matProcessedInput, cv::Size(41,41), 0, 0, cv::BORDER_DEFAULT);

            //Convert between OpenCV and Qt colorspaces
            cv::cvtColor(this->matRawInput, this->matRawInput, CV_BGR2RGB);
            cv::cvtColor(this->matProcessedInput, this->matProcessedInput, CV_BGR2RGB);

            //Let's protect our shared QImage memory...

            *this->globalRawImage.data() = QImage((uchar*)matRawInput.data, matRawInput.cols, matRawInput.rows, matRawInput.step, QImage::Format_RGB888);
            *this->globalProcessedImage.data() = QImage((uchar*)matProcessedInput.data, matProcessedInput.cols, matProcessedInput.rows, matProcessedInput.step, QImage::Format_RGB888);
            //qDebug() << "Reading Webcam";

        }
        this->pixelMutex->unlock();
        usleep(200);
    }
    quit();
}
