#include "organizer.h"
#include <QTextStream>
#include <QStringList>
#include <QFile>

Organizer::Organizer()
{
    tasks = new(QStack<Task>);
    QFile file (":/tasks/TaskList.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QStringList list = stream.read(file.size()).split("\n\n");
        for(int i = 0; i<list.size(); i++)
        {
            tasks->push(Task(list[i]));
        }

    }
}

Organizer::~Organizer()
{
    SaveTasks();
}

void Organizer::AddTask(Task newTask)
{
    tasks->push(newTask);
}

void Organizer::ReadTasks()
{
    QFile file (":/tasks/TaskList.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QStringList list = stream.read(file.size()).split("\n\n");
        for(int i = 0; i<list.size(); i++)
        {
            tasks->push_back(Task(list[i]));
        }

        file.close();

    }
}

void Organizer::SaveTasks()
{
    QFile file (":/tasks/TaskList.txt");
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream.readAll();
        for(int i = 0; i<tasks->size(); i++)         stream << "\n" << tasks->pop().TaskToText();
    }
    file.close();
}

void Organizer::taskPullThrough(QString name, QString deadline, QString progress)
{
    tasks->push(Task(name, deadline, progress));
}

void Organizer::buttonPress(QString name, QString deadline, QString progress)
{
    taskPullThrough(name, deadline, progress);
    SaveTasks();
}
