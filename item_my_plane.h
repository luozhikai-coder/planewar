#ifndef ITEM_PLANE_H
#define ITEM_PLANE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include "qpixmapitem.h"
#include "item_my_bullet.h"
#include "item_prop.h"
#include "item_boom.h"
class item_my_plane : public qpixmapItem
{
public:
    item_my_plane(const QString &fileName, QGraphicsScene *scene,int my_plane_type);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    int blood;
};

#endif // ITEM_PLANE_H
