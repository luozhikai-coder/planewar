#include "qpixmapitem.h"

qpixmapItem::qpixmapItem(const QString &filename,QGraphicsScene *scene,int type)
{
    pixmap.load(filename);
    this->scene = scene;
    scene->addItem(this);
    this->type = type;
}

QRectF qpixmapItem::boundingRect() const
{
    return QRectF(QPointF(0,0),this->pixmap.size());
}
void qpixmapItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->drawPixmap(0,0,this->pixmap);
}

QPixmap qpixmapItem::getQpixmap()
{
    return this->pixmap;
}


