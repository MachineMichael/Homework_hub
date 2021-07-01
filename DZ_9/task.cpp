#include "task.h"

Task::Task()
{
    data = new(QStringList);
}

Task::Task(QString name, QString deadline, QString progress)
{
    data = new(QStringList);
    data->append(name);
    data->append(deadline);
    data->append(progress);
}

Task::Task(QString str)
{
    data = new(QStringList);
    data->append(str.split("\n"));
}

//Task::~Task()
//{
//    delete (this);
//}

void Task::TextToTask(QString str)
{
    data->append(str.split("\n"));
}

QString Task::TaskToText()
{
    QString str;
    for(int i = 0; i<data->size(); i++)
    {
        str.append((*data)[i]);
        str.append("\n");
    }
    return str;
}
