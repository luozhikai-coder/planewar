#include "item_enemy_bullet.h"

extern bool gameOverFlag;

item_enemy_bullet::item_enemy_bullet(const QString &filename,QGraphicsScene *sence,int bullet_type)
    :qpixmapItem(filename,sence,bullet_type)
{
     this->speed_x=qrand()%10;
     this->speed_y=qrand()%20+10;
//    if(this->speed_y<=4&&this->speed_y>=-4)
//      this->speed_y=10;

}
//QRectF item_enemy_bullet::boundingRect() const
//{
//    return QRectF(0,0,this->getQpixmap().width(),this->getQpixmap().height());
//}
void item_enemy_bullet::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)//重写用来绘制item内容
{
    painter->drawPixmap(0,0,this->getQpixmap());//重新绘制
    if(this->collidingItems().count()>0)
    {
        item_my_plane *myplane;
        myplane=(item_my_plane *)(collidingItems().first());
        if(myplane->type<4)
        {
            qDebug()<<"MYPLANE BLOOD -5";
            myplane->blood-=20;
            if(myplane->blood < 0)
            {
               myplane->hide();
               item_boom *myboom = new item_boom("image/hero_blowup_n4.png",this->scene,1);
//                 myboom->setPos(mapToScene(0,0));
               gameOverFlag = true;
            }
            docolliding();
        }
    }

}
void  item_enemy_bullet::docolliding()
{
    item_boom *enemy_bomb=new item_boom("image/enemy1_down4.png",this->scene,1);
    enemy_bomb->setPos(mapToScene(0,0));

    delete this;

}
void item_enemy_bullet::advance(int phase)
{
    if(mapToScene(0,0).y()<0||mapToScene(0,0).y()>800||mapToScene(0,0).x()<0||mapToScene(0,0).x()>400)
    {
        delete this;
    }
    else
    {
        this->setPos(mapToScene(speed_x,speed_y));
    }
}
