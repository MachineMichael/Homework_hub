#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTranslator>
#include <QFileSystemModel>

#include "filebrowser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:

    void chooseLang(int);

    void setRead(int);

    void openTxt();

    void saveTxt();

    void chooseStyle(int);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void keyPressEvent(QKeyEvent *) override;

    void changeEvent(QEvent * event) override;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void switchLang(int);

    void open();

    void saveAs();

    void create();

    void quitProgram();

    void switchRead(int);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void switchStyle(int);

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;

    QStringList getData(const QString& html);

    QTranslator translator;

    FileBrowser *fileBrowser;

};
#endif // MAINWINDOW_H
