#include "item_my_bullet.h"


extern int gamescore;

item_my_bullet::item_my_bullet(const QString &fileName, QGraphicsScene *scene) :
    qpixmapItem(fileName, scene, BULLET_TYPE_MY1)
{
    qDebug()<<"new item_my_bullet";
}

void item_my_bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->drawPixmap(0,0,this->getQpixmap());
     if(this->collidingItems().count()>0)
       {
           item_enemy_plane *enemyplane;
           enemyplane=(item_enemy_plane *)(collidingItems().first());
           if(enemyplane->type == ENEMY1)
              {
               qDebug()<<"ENEMY BLOOD -50";
               enemyplane->blood-=50;
               if(enemyplane->blood<0)
               {
                   enemyplane->setPos(qrand()%400,-100);
                   enemyplane->blood = ENEMY1;
                    gamescore+=10;
               }
               docolliding();
           }
           else if(enemyplane->type == ENEMY2)
           {
               qDebug()<<"ENEMY BLOOD -30";
               enemyplane->blood-=30;
               if(enemyplane->blood < 0)
               {
                   enemyplane->setPos(qrand()%400,-100);
                   enemyplane->blood = ENEMY2;
                    gamescore+=20;
               }
               docolliding();
           }
           else if(enemyplane->type == ENEMY3)
           {
               qDebug()<<"ENEMY BLOOD -20";
               enemyplane->blood-=20;
               if(enemyplane->blood < 0)
               {
//                   delete enemyplane;
                   enemyplane->setPos(qrand()%200+100,-800);
                   enemyplane->blood = ENEMY3;
                   gamescore+=30;
               }
               docolliding();
           }

       }
//     for(int i = 0;i<this->collidingItems().size();++i)
//     {
//         if(((qpixmapItem *)this->collidingItems()[i])->type == ENEMY1)
//         {
//              qDebug()<<"ENEMY1 BLOOD -20";
//              ((item_enemy_plane *)this->collidingItems()[i])->blood-=20;

//              if(((item_enemy_plane *)this->collidingItems()[i])->blood < 0)
//              {
//                this->collidingItems()[i]->setPos(qrand()%400,-100);
//                gamescore+=10;
//              }

//         }
//         else if(((qpixmapItem *)this->collidingItems()[i])->type == ENEMY2)
//         {
//               qDebug()<<"ENEMY1 BLOOD -10";
//               ((item_enemy_plane *)this->collidingItems()[i])->blood-=10;

//               if(((item_enemy_plane *)this->collidingItems()[i])->blood < 0)
//               {
//                  this->collidingItems()[i]->setPos(qrand()%400,-100);
//                  gamescore+=20;

//               }
//         }
//         else if(((qpixmapItem *)this->collidingItems()[i])->type == ENEMY3)
//         {
//             qDebug()<<"ENEMY1 BLOOD -5";
//             ((item_enemy_plane *)this->collidingItems()[i])->blood-=5;

//             if(((item_enemy_plane *)this->collidingItems()[i])->blood < 0)
//             {
//                 delete this->collidingItems()[i];
//                 gamescore+=30;

//             }
//         }

//     }
}

void item_my_bullet::advance(int phase)
{
    this->setPos(mapToScene(0,0).x(),mapToScene(0,0).y()-40);
    if(mapToScene(0,0).y()<0)
    {
        delete this;
    }
}

void item_my_bullet::docolliding()
{
    item_boom *enemy_bomb=new item_boom("image/enemy1_down4.png",this->scene,1);
    enemy_bomb->setPos(mapToScene(0,0));

    delete this;
}

bool item_my_bullet::hasPlane(QList<QGraphicsItem *> itemList)
{
    QList<QGraphicsItem *>::iterator i;
    qpixmapItem *item;
    i = itemList.begin();
    while(i!=itemList.end())
    {
        item = (qpixmapItem*)(*i);
        if(item->type >=101)
        {

            return true;
        }
        i++;
    }
    return false;
}


