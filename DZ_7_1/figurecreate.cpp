#include "figurecreate.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

FigureCreate::FigureCreate(QObject *parent) : QObject(parent), QGraphicsItem()
{
    x = 0;
    y = 0;
    brush.setColor(QColor(rand() % 256, rand() % 256 , rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    setPos(0,0);
    moving = false;
}

void FigureCreate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(brush);

    if (geometry == 0) painter->drawRect(x, y, 200, 100);
    if (geometry == 1) painter->drawEllipse(x, y, 200, 100);
    if (geometry == 2) painter->drawPie(x, y, 200, 100, 30*16, 120*16);

}

QRectF FigureCreate::boundingRect() const
{
    return QRectF(x, y, 200, 100);
}

void FigureCreate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
          moving = true;
          bpoint = event->pos().toPoint();
    }
    if (event->button() == Qt::RightButton)
    {
        this->hide();
        this->deleteLater();
        emit reDraw();
    }
}

void FigureCreate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
          moving = false;
          emit reDraw();
    }
}

void FigureCreate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving)
    {
        QPoint p = event->pos().toPoint() - bpoint;
        x += p.x();
        y += p.y();
        bpoint = event->pos().toPoint();
        emit reDraw();
    }
}






