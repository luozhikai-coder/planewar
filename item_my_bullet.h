#ifndef ITEM_MY_BULLET_H
#define ITEM_MY_BULLET_H

#include <QDebug>
#include "qpixmapitem.h"
#include "item_enemy_plane.h"

class item_my_bullet : public qpixmapItem
{
public:
    explicit item_my_bullet(const QString &fileName, QGraphicsScene *scene);
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   void docolliding();
   void advance(int phase);
   bool hasPlane(QList<QGraphicsItem *> itemList);
  //  QRectF boundingRect() const;

signals:

public slots:

};

#endif // ITEM_MY_BULLET_H
