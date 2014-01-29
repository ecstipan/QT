#include "mvideothread.h"
#include <QtCore>
#include <QDebug>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QSharedData>
#include <QSharedDataPointer>
#include "main.h"
extern

mVideoThread::mVideoThread(QMutex* pixel)
{
    pixelMutex = pixel;
    shutdown = false;
    cameraFPS = 25;
    cameraW = 1920;
    cameraH = 1080;
}

void mVideoThread::run()
{
    shutdown = false;

    while (!shutdown) {
        this->pixelMutex->lock();
        if (cameraObject->isOpened()) {
            this->cameraObject->read(matRawInput);
            if (matRawInput.empty() == false) {
                //Do some blur processing...
                cv::GaussianBlur(this->matRawInput, this->matProcessedInput, cv::Size(41,41), 0, 0, cv::BORDER_DEFAULT);
                //this->matProcessedInput = this->matRawInput;

                //Convert between OpenCV and Qt colorspaces
                cv::cvtColor(this->matRawInput, this->matRawInput, CV_BGR2RGB);
                cv::cvtColor(this->matProcessedInput, this->matProcessedInput, CV_BGR2RGB);

                //Scale everything to 1080p for constand processing times
                //This also makes resampling an easier algorythm
                if(cameraW != 1920)
                cv::resize(this->matProcessedInput, this->matProcessedInput, cv::Size(1920, 1080), 0, 0, cv::INTER_NEAREST);

                //Let's protect our shared QImage memory...
                *this->globalRawImage.data() = QImage((uchar*)matRawInput.data, matRawInput.cols, matRawInput.rows, matRawInput.step, QImage::Format_RGB888);
                *this->globalProcessedImage.data() = QImage((uchar*)matProcessedInput.data, matProcessedInput.cols, matProcessedInput.rows, matProcessedInput.step, QImage::Format_RGB888);
            }
        }
        this->pixelMutex->unlock();
        msleep(1.0/this->cameraFPS*100);
    }
    quit();
}
