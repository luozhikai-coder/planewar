#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QString>
#include <QDebug>
#include <QGraphicsScene>


enum{
    PLANE_TYPE_MY1 = 1,
    PLANE_TYPE_MY2,
    PLANE_TYPE_MY3,
    BULLET_TYPE_MY1,
    BULLET_TYPE_MY2,
    BULLET_TYPE_MY3,
    PROP_TYPE1,
    PROP_TYPE2
};


enum{
    ENEMY1 = 100,
    ENEMY2 = 150,
    ENEMY3 = 200
};

//#define PLANE_TYPE_MY 1
//#define BULLET_TYPE 2
//#define PLANE_TYPE_ENEMY 3

class qpixmapItem:public QGraphicsItem
{
public:
    qpixmapItem(const QString &filename,QGraphicsScene *scene,int type);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QPixmap getQpixmap();
    int type;
    QGraphicsScene *scene;
protected:
   QPixmap pixmap;

};

#endif // QPIXMAPITEM_H
