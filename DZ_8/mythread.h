#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>


class MyThread : public QThread
{
public:
    MyThread();
    void run() override;
};

#endif // MYTHREAD_H
