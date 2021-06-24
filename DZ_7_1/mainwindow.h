#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include "figurecreate.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene* scene;
    FigureCreate* fc1;
    qint8 geoCount = 0;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void reDraw();


};
#endif // MAINWINDOW_H
