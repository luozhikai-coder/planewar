#include "item_enemy_plane.h"

item_enemy_plane::item_enemy_plane(const QString &filename,QGraphicsScene *sence,int enemy_type)
    :qpixmapItem(filename, sence,enemy_type)
{
     xpos_speed=2+qrand()%3;
     ypos_speed=2+qrand()%3;

     setPos(200,-100);
     blood=enemy_type;
}
void item_enemy_plane::advance(int phase)
{
    static int i=0;

    if(mapToScene(0,0).y()>=852)
    {
        setPos(40+qrand()%350,-80);
        ypos_speed=2+qrand()%3;
    }
    else if(mapToScene(0,0).x()<=0||mapToScene(0,0).x()>360)
    {
        this->xpos_speed=-(xpos_speed);
    }


    this->setPos(mapToScene(xpos_speed,ypos_speed));//mapToScene(0,0)����Ŀ�굱ǰ��λ�� ÿ����ʱ��ʱ����X��Y�ƶ��ľ���
    //һ��ʱ�������ӵ�
    if(i++%40==0)
    {
        this->creatbullet();
    }
}
void item_enemy_plane::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)//��д��������item����
{
    painter->drawPixmap(0,0,this->getQpixmap());//���»���
}

void item_enemy_plane::creatbullet()
{
    item_enemy_bullet *enemybullet=new item_enemy_bullet("image/bullet.png",this->scene,BULLET_TYPE_MY2);
    enemybullet->setPos(mapToScene(0,0));
}
