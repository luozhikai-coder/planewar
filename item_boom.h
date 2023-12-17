#ifndef ITEM_BOOM_H
#define ITEM_BOOM_H
#include "qpixmapitem.h"

class item_boom:public qpixmapItem
{
public:
     explicit item_boom(const QString &fileName, QGraphicsScene *scene,int boom_type);
    void advance(int phase);
};

#endif // ITEM_BOOM_H
