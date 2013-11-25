#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include "mallthreads.h"
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

    void updateRawVideo(QImage img);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
