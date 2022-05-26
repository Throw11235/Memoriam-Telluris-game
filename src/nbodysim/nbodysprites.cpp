#include "nbodysprites.h"
#include <QPainter>

NBodySprite::NBodySprite(NBody * toConnect, QString sprite)
{
    connectedBody = toConnect;
    pathToSpriteFile = sprite;
}


void NBodySprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->beginNativePainting();

  //  painter->drawEllipse(connectedBody->getFullCoords(),connectedBody->getRadius() * 2, connectedBody->getRadius() * 2);

    painter->endNativePainting();
}

QRectF NBodySprite::boundingRect() const
{

    return QRectF(-10, -10, 20,20);
}

void NBodySprite::advance(int step){
    if(!step){
        return;
    }
   // setPos(connectedBody->get());
}

