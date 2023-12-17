#ifndef ITEM_PROP_H
#define ITEM_PROP_H

#include "qpixmapitem.h"


class item_prop:public qpixmapItem
{
public:
    item_prop(const QString &fileName, QGraphicsScene *scene,int prop_type);
    void advance(int phase);
    void propHide();
};

#endif // ITEM_PROP_H
