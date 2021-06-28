#include "filebrowser.h"
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QtDebug>

FileBrowser::FileBrowser(QWidget *parent) : QWidget(parent)
{
    table = new QTableView(this);
    line = new QLineEdit(this);
    line->setReadOnly(true);
    lineSearch = new QLineEdit(this);
    label = new QLabel(this);
    label->setText(tr("Директория проекта:"));
    searchButton = new QPushButton(tr("Поиск (введите имя файла или папки в строку ниже)"), this);

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
    layout->addWidget(searchButton);
    layout->addWidget(lineSearch);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(SearchDir()));
}

QString FileBrowser::find_file(QString dir, QString name) {
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
      it.next();
      if (it.fileName() == name) {
        return it.filePath();
      }
    }
    return QString();
  }

void FileBrowser::SearchDir() {

    qDebug() << model->index(find_file(model->rootPath(), lineSearch->text()));
    table->setCurrentIndex(model->index(find_file(model->rootPath(), lineSearch->text())));


}
