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
private:
    ConsoleWindow *consoleWindow;
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
public slots:
    void openConsoleWindow();
private slots:
    void closeProgram();
    void handleEnable();
    void handleDisable();
    void handleUseDevice();
    void handleDropDownCamSelect(int cam);
    void handleResButton();
    void handleFPSButton();
    void handleBoxRes(int index);
    void handleBoxFPS(int index);
};

#endif // MAINWINDOW_H
