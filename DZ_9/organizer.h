#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QObject>
#include <QStack>
#include <QFile>

#include "task.h"

class Organizer: public QObject
{
    Q_OBJECT
public:
    Organizer();
    ~Organizer();
    void AddTask(Task);
    void ReadTasks();
    void SaveTasks();
    void taskPullThrough(QString, QString, QString);
    Q_INVOKABLE void buttonPress(QString, QString, QString);
private:
    QStack<Task> *tasks;
};

#endif // ORGANIZER_H
