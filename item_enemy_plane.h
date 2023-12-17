#ifndef ITEM_ENEMY_PLANE_H
#define ITEM_ENEMY_PLANE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include "qpixmapitem.h"
#include "item_my_plane.h"
#include "item_enemy_bullet.h"


class item_enemy_plane : public qpixmapItem
{
public:
    item_enemy_plane(const QString &fileName, QGraphicsScene *scene,int enemy_type);
//    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);//重写用来绘制item内容
    void advance(int phase);
    void creatbullet();
       int xpos_speed;
       int ypos_speed;
       int blood;
};

#endif // ITEM_ENEMY_PLANE_H
