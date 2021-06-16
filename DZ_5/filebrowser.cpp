#include "filebrowser.h"
#include <QVBoxLayout>
#include <QCoreApplication>

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    table = new QTableView(this);
    line = new QLineEdit(this);
    line->setReadOnly(true);
    label = new QLabel(this);
    label->setText(tr("Директория проекта:"));

    model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());
    model->setReadOnly(false);

    table->setModel(model);
    table->setRootIndex(model->index(QDir::rootPath()));

    line->setText(QCoreApplication::applicationDirPath());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table, 2);
    layout->addWidget(label);
    layout->addWidget(line);
}
