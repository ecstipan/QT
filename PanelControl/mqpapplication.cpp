#include "mqpapplication.h"
#include <QDebug>
MQPApplication::MQPApplication()
{

}
MQPApplication::~MQPApplication()
{
    //Kill our Threads
    this->mutex->lock();
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
}
