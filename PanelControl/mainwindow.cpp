//MQP Headers
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "main.h"
#include "mpanelstatus.h"
#include "mpanel.h"
#include "mvideothread.h"
#include "mnetworkthread.h"
#include "muithread.h"

#include "mainwindow.h"
#include <QApplication>
#include <QEvent>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mnetworksocket.h"

unsigned short int cameraCount = 0;
unsigned short int currentDropdownCamers = 0;
unsigned short int curResIndex = 0;
unsigned short int curFPSIndex = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isDisplayingVideo = false;

    cameraFPS = 25;
    cameraW = 1920;
    cameraH = 1080;
    this->uiHandleLeft = 0;
    this->uiHandleRight = 1279;
    this->uiHandleBottom = 719;
    this->uiHandleTop = 0;

    this->ui->resBox->addItem("1920 x 1080");
    this->ui->resBox->addItem("1600 x 900");
    this->ui->resBox->addItem("1280 x 720");
    this->ui->resBox->addItem("960 x 540");
    this->ui->resBox->addItem("640 x 360");
    this->ui->resBox->setCurrentIndex(0);

    this->ui->fpsBox->addItem("30 FPS");
    this->ui->fpsBox->addItem("25 FPS");
    this->ui->fpsBox->addItem("24 FPS");
    this->ui->fpsBox->addItem("10 FPS");
    this->ui->fpsBox->addItem("5 FPS");
    this->ui->fpsBox->addItem("1 FPS");
    this->ui->fpsBox->setCurrentIndex(1);

    this->ui->panelOveryalLabel->setAttribute(Qt::WA_TranslucentBackground);

    //initialize our windows
    consoleWindow = new ConsoleWindow();

    //Setup our slots and signals for faster processing...;
    connect(ui->enableButton, SIGNAL(clicked()), this, SLOT(handleEnable()));
    connect(ui->disableButton, SIGNAL(clicked()), this, SLOT(handleDisable()));
    connect(ui->useDevice, SIGNAL(clicked()), this, SLOT(handleUseDevice()));
    connect(ui->cameraSelect, SIGNAL(activated(int)), this, SLOT(handleDropDownCamSelect(int)));
    connect(ui->resButton, SIGNAL(clicked()), this, SLOT(handleResButton()));
    connect(ui->fpsButton, SIGNAL(clicked()), this, SLOT(handleFPSButton()));
    connect(ui->resBox, SIGNAL(activated(int)), this, SLOT(handleBoxRes(int)));
    connect(ui->fpsBox, SIGNAL(activated(int)), this, SLOT(handleBoxFPS(int)));

    connect(ui->actionDebug_Console, SIGNAL(triggered()), this, SLOT(openConsoleWindow()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeProgram()));
    connect(ui->actionReset_Array, SIGNAL(triggered()), this, SLOT(resetArray()));


    connect(ui->actionColor_Space_Test, SIGNAL(triggered()), this, SLOT(setTestPattern1()));
    connect(ui->actionContrast_Test, SIGNAL(triggered()), this, SLOT(setTestPattern2()));
    connect(ui->actionScaling_AA_Test, SIGNAL(triggered()), this, SLOT(setTestPattern3()));
    connect(ui->actionNone, SIGNAL(triggered()), this, SLOT(setTestPattern0()));
}

void MainWindow::closeProgram()
{
    this->close();
}

void MainWindow::resetArray()
{
    beginReaddressProcess();
}

void MainWindow::openConsoleWindow()
{
    consoleWindow->show();
}

void MainWindow::addConsoleLogEvent(QString stuff)
{
    this->consoleWindow->addLog(stuff);
}

void MainWindow::setTestPattern1()
{
    setTestPattern(1);
    isDisplayingVideo = true;
}

void MainWindow::setTestPattern2()
{
    setTestPattern(2);
    isDisplayingVideo = true;
}

void MainWindow::setTestPattern3()
{
    setTestPattern(3);
    isDisplayingVideo = true;
}

void MainWindow::setTestPattern0()
{
    setTestPattern(0);
    isDisplayingVideo = true;
}

MainWindow::~MainWindow()
{
    //Kill our Threads

    delete ui;
}

void MainWindow::updateRawVideo(QImage img)
{
    if (!img.isNull()){
        if (this->cameraW != 1280) {
            QImage temp = img.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::FastTransformation);
            this->ui->rawLabel->setPixmap(QPixmap::fromImage(temp));
        } else {
            this->ui->rawLabel->setPixmap(QPixmap::fromImage(img));
        }
    }
}

void MainWindow::updateArrayOverlay()
{
    QPixmap pixmap(1280,720);
    pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    //painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(40, 255, 40, 128)));

    //setup our blocks
    unsigned int blockx, blocky;
    //sweep thorugh each block
    for (blockx = 0; blockx < MPanel::arrayWidth; blockx++)
    {
        for (blocky = 0; blocky < MPanel::arrayHeight; blocky++)
        {
            //Add a block if there's a panel
            if (MPanel::panelExistsAt(MPanel::boundLeft + blockx,
                                      MPanel::boundTop + blocky)) {
                //so we have a panel!
                //let's check if it's healthy
                if (MPanel::getPanelAtLocation(MPanel::boundLeft + blockx,
                                               MPanel::boundTop + blocky)->hasFault()) {
                    //We're broken :(
                    painter.setBrush(QBrush(QColor(255, 50, 50, 70)));
                } else {
                    //The panel is fine!
                    painter.setBrush(QBrush(QColor(255, 255, 255, 40)));
                }
                //so we have our status, let's draw our rectangle
                int pos_x, pos_y, pan_w, pan_h;

                pan_w = (uiHandleRight - uiHandleLeft)/MPanel::arrayWidth;
                pan_h = (uiHandleBottom - uiHandleTop)/MPanel::arrayHeight;

                pos_x = uiHandleLeft + pan_w*blockx;
                pos_y = uiHandleTop + pan_h*blocky;

                painter.drawRect(pos_x, pos_y, pan_w, pan_h);
            } //if not, we'll draw nothing
        }
    }

    //update the UI
    this->ui->panelOveryalLabel->setPixmap(pixmap);
}

void MainWindow::handleEnable()
{
    logConsole(QString("Enabling video input..."));
    openCamera();
}

void MainWindow::handleDisable()
{
    logConsole(QString("Disabling video input..."));
    closeCamera();
    this->ui->rawLabel->clear();
}

void MainWindow::handleUseDevice()
{
    qDebug() << "Setting...";
    selectCamera(currentDropdownCamers);
}

void MainWindow::addCameraToSelector()
{
    //finding cameras n shit
    std::ostringstream camname;
    camname << "Camera Input Source #" <<cameraCount++;
    this->ui->cameraSelect->addItem(camname.str().c_str());
}

void MainWindow::handleDropDownCamSelect(int cam)
{
    currentDropdownCamers=cam;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //kill our windows
    shutdownArray();
    closeUDP();
    qDebug() << "Closing child windows...";
    consoleWindow->destroy = true;
    consoleWindow->close();
    consoleWindow->~ConsoleWindow();

    if (thread1) {
        qDebug() << "Stopping Video Thread...";
        thread1->shutdown=true;
        if(!thread1->wait(1000)) //Wait until it actually has terminated (max. 5 sec)
        {
          qWarning("Thread deadlock detected, bad things may happen !!!");
          thread1->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
          thread1->wait(); //Note: We have to wait again here!
        } else qDebug("Stopped!");
    }
    if (thread2) {
        qDebug() << "Stopping Network Thread...";
        thread2->shutdown=true;
        if(!thread2->wait(1000)) //Wait until it actually has terminated (max. 5 sec)
        {
          qWarning("Thread deadlock detected, bad things may happen !!!");
          thread2->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
          thread2->wait(); //Note: We have to wait again here!
        } else qDebug("Stopped!");
    }
    if (thread3) {
        qDebug() << "Stopping UI Thread...";
        thread3->shutdown=true;
        if(!thread3->wait(1000)) //Wait until it actually has terminated (max. 5 sec)
        {
          qWarning("Thread deadlock detected, bad things may happen !!!");
          thread3->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
          thread3->wait(); //Note: We have to wait again here!
        } else qDebug("Stopped!");
    }
    qDebug() << "THreads stopped.  Finishing closing...";
    QMainWindow::closeEvent(event);
}

void MainWindow:: handleResButton()
{
    setResolution(curResIndex);
    //openCamera();
}
void MainWindow::handleFPSButton()
{
    setFPS(curFPSIndex);
    //openCamera();
}
void MainWindow::handleBoxRes(int index)
{
    curResIndex = index;
}
void MainWindow::handleBoxFPS(int index)
{
    curFPSIndex = index;
}

void MainWindow::on_sliderX_valueChanged(int value)
{
    uiHandleLeft = value;
    setOffsetXStart(value);
    this->ui->sliderW->setMinimum(uiHandleLeft+99);
}

void MainWindow::on_sliderY_valueChanged(int value)
{
    uiHandleTop = value;
    setOffsetYStart(value);
    this->ui->sliderH->setMinimum(uiHandleTop+99);
}

void MainWindow::on_sliderW_valueChanged(int value)
{
    uiHandleRight = value;
    setOffsetXEnd(value);
    this->ui->sliderX->setMaximum(uiHandleRight-99);
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    uiHandleBottom = value;
    setOffsetYEnd(value);
    this->ui->sliderY->setMaximum(uiHandleBottom-99);
}
