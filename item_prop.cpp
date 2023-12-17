#include "item_prop.h"

item_prop::item_prop(const QString &fileName, QGraphicsScene *scene,int prop_type)
    :qpixmapItem(fileName, scene,prop_type)
{

}

void item_prop::advance(int phase)
{
    this->setPos(mapToScene(0,0).x(),mapToScene(0,0).y()+5);
    if(mapToScene(0,0).y()>850)
        delete this;

}

void item_prop::propHide()
{
    delete this;
}
