#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include "mallthreads.h"
#include "consolewindow.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    mAllThreads* thread1;
    mAllThreads* thread2;
    mAllThreads* thread3;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isDisplayingVideo;
    void updateRawVideo(QImage img);
    void addCameraToSelector();
    QMutex *mutex;
    void addConsoleLogEvent(QString stuff);
    void updateArrayOverlay();

    unsigned int cameraFPS;
    unsigned int cameraW;
    unsigned int cameraH;

    unsigned int uiHandleLeft;
    unsigned int uiHandleRight;
    unsigned int uiHandleBottom;
    unsigned int uiHandleTop;
private:
    ConsoleWindow *consoleWindow;
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
public slots:
    void openConsoleWindow();
private slots:
    void resetArray();
    void closeProgram();
    void handleEnable();
    void handleDisable();
    void handleUseDevice();
    void handleDropDownCamSelect(int cam);
    void handleResButton();
    void handleFPSButton();
    void handleBoxRes(int index);
    void handleBoxFPS(int index);
    void on_sliderX_valueChanged(int value);
    void on_sliderY_valueChanged(int value);
    void on_sliderW_valueChanged(int value);
    void on_sliderH_valueChanged(int value);
    void setTestPattern1();
    void setTestPattern2();
    void setTestPattern3();
    void setTestPattern0();
};

#endif // MAINWINDOW_H
