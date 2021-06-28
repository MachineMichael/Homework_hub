#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QTableView>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit FileBrowser(QWidget *parent = nullptr);

signals:

private:

    QTableView *table;
    QFileSystemModel *model;
    QLineEdit *line;
    QLabel *label;
    QLineEdit *lineSearch;
    QPushButton *searchButton;

    QString find_file(QString, QString);

private slots:

    void SearchDir();

};

#endif // FILEBROWSER_H
