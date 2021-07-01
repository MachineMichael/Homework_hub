#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QStringList>


class Task
{
public:
    Task();
    Task(QString, QString, QString );
    Task(QString);
//    ~Task();
    void TextToTask(QString);
    QString TaskToText();
private:
    QStringList *data;
};

#endif // TASK_H
