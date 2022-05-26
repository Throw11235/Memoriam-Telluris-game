#include "masscenterindicator.h"
#include <QPainter>

MassCenterIndicator::MassCenterIndicator(Vessel * toConnect)
{
    connectedVessel = toConnect;
    setOpacity(0.5);
    setZValue(999);
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

void MassCenterIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if(connectedVessel != nullptr){
        painter->setBrush(QBrush(Qt::GlobalColor::yellow));
        painter->drawEllipse(QRectF(-5,-5,10,10));
    }
}

QRectF MassCenterIndicator::boundingRect() const
{

    return QRectF(-5,-5,10,10);
}

void MassCenterIndicator::advance(int step){
    if(!step){
        return;
    }
    if(connectedVessel != nullptr){
        this->setPos(connectedVessel->getMassCenterCoords().toPointF());
    }
}
