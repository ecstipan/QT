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

#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    this->ui->resBox->addItem("1920 x 1080");
    this->ui->resBox->addItem("1600 x 900");
    this->ui->resBox->addItem("1280 x 720");
    this->ui->resBox->addItem("960 x 540");
    this->ui->resBox->addItem("640 x 360");

    this->ui->fpsBox->addItem("30 FPS");
    this->ui->fpsBox->addItem("25 FPS");
    this->ui->fpsBox->addItem("24 FPS");
    this->ui->fpsBox->addItem("10 FPS");
    this->ui->fpsBox->addItem("5 FPS");
    this->ui->fpsBox->addItem("1 FPS");

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
}

void MainWindow::closeProgram()
{
    this->close();
}

void MainWindow::openConsoleWindow()
{
    consoleWindow->show();
}

void MainWindow::addConsoleLogEvent(QString stuff)
{
    this->consoleWindow->addLog(stuff);
}

MainWindow::~MainWindow()
{
    //Kill our Threads
    if(this->mutex) this->mutex->lock();
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
    delete ui;
}

void MainWindow::updateRawVideo(QImage img) {
    QImage temp = img.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    this->ui->rawLabel->setPixmap(QPixmap::fromImage(temp));
}

void MainWindow::handleEnable(){
    logConsole(QString("Enabling video input..."));
    openCamera();
}

void MainWindow::handleDisable(){
    logConsole(QString("Disabling video input..."));
    closeCamera();
    this->ui->rawLabel->clear();
}

void MainWindow::handleUseDevice(){
    qDebug() << "Setting...";
    selectCamera(currentDropdownCamers);
}

void MainWindow::addCameraToSelector() {
    //finding cameras n shit
    std::ostringstream camname;
    camname << "Camera Input Source #" <<cameraCount++;
    this->ui->cameraSelect->addItem(camname.str().c_str());
}

void MainWindow::handleDropDownCamSelect(int cam) {
    currentDropdownCamers=cam;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    //kill our windows
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

void MainWindow:: handleResButton(){
    setResolution(curResIndex);
    openCamera();
}
void MainWindow::handleFPSButton(){
    setFPS(curFPSIndex);
    openCamera();
}
void MainWindow::handleBoxRes(int index){
    curResIndex = index;
}
void MainWindow::handleBoxFPS(int index){
    curFPSIndex = index;
}
