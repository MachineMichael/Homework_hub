#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTranslator>

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

protected:
    void changeEvent(QEvent * event) override;

private slots:
    void addNewTab();
    void deleteCurrentTab();
    void switchToRus();
    void switchToEng();
    void sendToPrint();

};
#endif // MAINWINDOW_H
