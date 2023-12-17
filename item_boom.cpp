#include "item_boom.h"



item_boom::item_boom(const QString &fileName, QGraphicsScene *scene,int boom_type) :
    qpixmapItem(fileName, scene, boom_type)
{

}



void item_boom::advance(int phase)
{
    delete this;
}
