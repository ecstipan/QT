#include "mvideothread.h"
#include <QtCore>
#include <QDebug>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QSharedData>
#include <QSharedDataPointer>
#include <QColor>
#include "main.h"
#include "mpanel.h"

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

        //get our frame from some source
        QImage processedImage;
        matRawInput = cv::imread("default.bmp", CV_LOAD_IMAGE_COLOR);

        if(*this->testPattern == 1)
        {
            //qDebug() << "We should be displaying image 1";
            matRawInput = cv::imread("test1.bmp",3);
        }
        else if (*this->testPattern == 2)
        {
          // qDebug() << "We should be displaying image 2";
           matRawInput = cv::imread("test2.bmp",3);
        }
        else if (*this->testPattern == 3)
        {
            //qDebug() << "We should be displaying image 3";
            matRawInput = cv::imread("test3.bmp",3);
        }
        else if (*this->testPattern == 0 && cameraObject->isOpened())
        {
            //qDebug() << "We should be displaying camera";
            this->cameraObject->read(matRawInput);
        } else {
            //qDebug() << "We should be displaying nothing";
        }

        //process our frame and send to GUI
        if (matRawInput.empty() == false) {
            //Do some blur processing...
            cv::cvtColor(this->matRawInput, this->matRawInput, CV_BGR2RGB);
            cv::GaussianBlur(this->matRawInput, this->matProcessedInput, cv::Size(41,41), 0, 0, cv::BORDER_DEFAULT);
            //this->matProcessedInput = this->matRawInput;

            //Scale everything to 1080p for constand processing times
            //This also makes resampling an easier algorythm
            cv::resize(this->matProcessedInput, this->matProcessedInput, cv::Size(1920, 1080), 0, 0, cv::INTER_NEAREST);

            //Let's protect our shared QImage memory...
            processedImage = QImage((uchar*)matProcessedInput.data, matProcessedInput.cols, matProcessedInput.rows, matProcessedInput.step, QImage::Format_RGB888);
            *this->globalRawImage.data() = QImage((uchar*)matRawInput.data, matRawInput.cols, matRawInput.rows, matRawInput.step, QImage::Format_RGB888);
            *this->globalProcessedImage.data() = processedImage;


            if (!globalRawImage.isNull() && globalRawImage.data()->isNull() == false) {
                QImage temp = *globalRawImage.data();
                this->parentWindow->updateRawVideo(temp);
            }

        }

        //perform our redraw operation
        //updateOverlay();

        //Send our frame to the panels
        int inputHeight = 720;
        int inputWidth = 1280;
        unsigned int blockx, blocky;
        //sweep thorugh each block
        if (!processedImage.isNull())
        for (blockx = 0; blockx < MPanel::arrayWidth; blockx++)
        {
            for (blocky = 0; blocky < MPanel::arrayHeight; blocky++)
            {
                //Add a block if there's a panel
                if (MPanel::panelExistsAt(MPanel::boundLeft + blockx,
                                          MPanel::boundTop + blocky)) {
                    //so we have a panel!
                    //let's check if it's healthy
                    QString panelIP = MPanel::getPanelAtLocation(MPanel::boundLeft + blockx, MPanel::boundTop + blocky)->IPAddress;
                    int panelDim = MPanel::getPanelAtLocation(MPanel::boundLeft + blockx, MPanel::boundTop + blocky)->getDimension();

                    //the fun video processing funtime
                    //find our crop frame
                    int XcropStart = (1920*(1.0*(*this->uiHandleLeft+1)/inputWidth));
                    int XcropEnd = (1920*(1.0*(*this->uiHandleRight+1)/inputWidth));
                    int YcropStart = (1080*(1.0*(*this->uiHandleTop+1)/inputHeight));
                    int YcropEnd = (1080*(1.0*(*this->uiHandleBottom+1)/inputHeight));

                    //so we have array dimensions, let's find which panel we are
                    int pos_x, pos_y, pan_w, pan_h;
                    pan_w = (XcropEnd - XcropStart)/MPanel::arrayWidth;
                    pan_h = (YcropEnd - YcropStart)/MPanel::arrayHeight;
                    pos_x = XcropStart + pan_w*blockx;
                    pos_y = YcropStart + pan_h*blocky;

                    //crop our image
                    QImage cropped = processedImage.copy( pos_x-1, pos_y-1, pan_w-1, pan_h-1);
                    //QImage cropped = processedImage.copy( 0, 0, 1920, 1080);

                    //resize the image to be 16x16
                    QImage scaled = cropped.scaled(panelDim, panelDim, Qt::IgnoreAspectRatio, Qt::FastTransformation);

                    //convert scaled iamge to a byte array
                    char test[scaled.height()*scaled.width()*3];

                    //make a new heaer
                    QByteArray videoFrame(256*3, 0);
                    QByteArray header(2, 255);//source address
                    header.append(MPanel::boundLeft + blockx).append(MPanel::boundTop + blocky);//destination address
                    header.append((char)1); //For Video frame data
                    header.append((char)(0)); //This is the first 16x16 chunk

                    unsigned int i = 0;

                    //get our byte frame
                    for ( int row = 0; row < scaled.height(); row++ )
                        for ( int col = 0; col < scaled.width(); col++ )
                        {
                            QColor pixel(scaled.pixel(col,row));
                            test[i++] = (char)pixel.red();
                            test[i++] = (char)pixel.green();
                            test[i++] = (char)pixel.blue();
                        }

                    videoFrame = QByteArray(test, scaled.byteCount());

                    sendVideoFrame(panelIP.toStdString().c_str(), videoFrame.prepend(header));

                } //if not, we'll draw nothing
            }
        }

        this->pixelMutex->unlock();
        msleep(33);
    }
    quit();
}
