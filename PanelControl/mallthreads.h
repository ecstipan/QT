#ifndef MALLTHREADS_H
#define MALLTHREADS_H

#include <QtCore>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class mAllThreads : public QThread
{
    Q_OBJECT
public:
    explicit mAllThreads(QObject *parent = 0);
    bool shutdown;
signals:

public slots:

};

#endif // MALLTHREADS_H
