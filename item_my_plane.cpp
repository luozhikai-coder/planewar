#include "item_my_plane.h"
extern int bulletFlag;
int bombFlag;
extern bool gameOverFlag;
item_my_plane::item_my_plane(const QString &fileName, QGraphicsScene *scene,int my_plane_type)
    : qpixmapItem(fileName, scene, my_plane_type)
{
//    qDebug()<<"new item_my_plane";
    qDebug()<<this->type;
    blood = 500*this->type;
}

QRectF item_my_plane::boundingRect() const
{
    return QRectF(0,0,100,124);
}

void item_my_plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,this->pixmap);
    for(int i = 0;i<this->collidingItems().size();++i)
    {
        if(((qpixmapItem *)this->collidingItems()[i])->type == PROP_TYPE1)
        {
             qDebug()<<"道具1";
             this->collidingItems()[i]->hide();
             bulletFlag = 1;
//            this->collidingItems().removeAt(i);
        }
        else if(((qpixmapItem *)this->collidingItems()[i])->type == PROP_TYPE2)
        {
              qDebug()<<"道具2";
              bombFlag++;
              this->collidingItems()[i]->hide();
        }
        else if(((qpixmapItem *)this->collidingItems()[i])->type >= ENEMY1)
        {
             qDebug()<<"MYPLANE BLOOD -100";
             this->blood-=100;
             if(this->blood < 0)
             {  
                this->hide();
                item_boom *myboom = new item_boom("image/hero_blowup_n4.png",this->scene,1);
//                 myboom->setPos(mapToScene(0,0));
                gameOverFlag = true;
             }

        }
    }
}


