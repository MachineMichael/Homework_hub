#ifndef FIGURECREATE_H
#define FIGURECREATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>

class FigureCreate : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)

public:
    explicit FigureCreate(QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
    qint8 geometry = 0;
signals:
    void reDraw();
    void mbWheel();
public slots:
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    int x, y;

    QPoint bpoint;
    bool moving;
    QBrush brush;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;


};

#endif // FIGURECREATE_H
