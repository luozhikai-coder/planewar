#ifndef ITEM_ENEMY_BULLET_H
#define ITEM_ENEMY_BULLET_H

#include "qpixmapitem.h"
#include "item_my_plane.h"
#include "item_boom.h"
class item_enemy_bullet : public qpixmapItem
{
public:
    explicit item_enemy_bullet(const QString &fileName, QGraphicsScene *scene,int bullet_type);
//    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);//重写用来绘制item内容
    void advance(int phase);
    void docolliding();
    int speed_x;
    int speed_y;
};

#endif // ITEM_ENEMY_BULLET_H
