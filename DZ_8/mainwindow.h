#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTranslator>
#include <QTextCharFormat>
#include <QTime>

#include "filebrowser.h"
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;

    QTranslator *translator;

    QTextCharFormat fmt;

    QDateTime today;

    FileBrowser* fileBrowser;

    MyThread *thread;

protected:
    void changeEvent(QEvent * event) override;

private slots:
    void addNewTab();
    void deleteCurrentTab();
    void switchToRus();
    void switchToEng();
    void sendToPrint();
    void copyStyle();
    void pasteStyle();
    void leftAlign();
    void rightAlign();
    void centerAlign();
    void fontStyle();
    void addDateTime();

};
#endif // MAINWINDOW_H
