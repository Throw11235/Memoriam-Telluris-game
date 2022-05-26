#include "vesselobjectsprite.h"
#include <src/object/vesselobject.h>
#include <QPainter>

VesselObjectSprite::VesselObjectSprite(QRectF sRect, QString sprite,  VesselObject * toConnect)
{
    spriteRectangle = sRect;
    pathToSpriteFile = sprite;
    connectedObject = toConnect;
}

void VesselObjectSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->beginNativePainting();

    QRectF target(-spriteRectangle.width()/2, -spriteRectangle.height()/2, spriteRectangle.width(), spriteRectangle.height());
    QRectF source = spriteRectangle;
    QPixmap pixmap(pathToSpriteFile);
    painter->drawPixmap(target, pixmap, source);

    painter->endNativePainting();
}

QRectF VesselObjectSprite::boundingRect() const
{

    return spriteRectangle;
}

void VesselObjectSprite::advance(int step){
    if(!step){
        return;
    }
    setPos(connectedObject->pos());
}
