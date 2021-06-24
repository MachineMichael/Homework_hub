#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    srand(clock());
    scene = new QGraphicsScene(this);
    setScene(scene);




}

MainWindow::~MainWindow()
{

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QGraphicsScene *sc = this->scene;
        FigureCreate *fc = new FigureCreate(this);
        fc->geometry = geoCount;
        if(geoCount == 2) geoCount = 0;
        else geoCount++;
        sc->addItem(fc);
        connect(fc, SIGNAL(reDraw()), this, SLOT(reDraw()));
        reDraw();
    }
}

void MainWindow::reDraw()
{
    scene->update();
    update();
}
