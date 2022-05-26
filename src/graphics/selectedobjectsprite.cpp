#include "selectedobjectsprite.h"
#include <QPainter>

SelectedVesselObjectSprite::SelectedVesselObjectSprite(QString sprite, VesselObject *connectedVesselObject)
{
    pathToSpriteFile = sprite;
    this->connectedVesselObject = connectedVesselObject;
}

void SelectedVesselObjectSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if(connectedVesselObject != nullptr){
       QRectF target = this->connectedVesselObject->boundingRect();
       QRectF source = QRectF(0,0,16,16);
       QPixmap pixmap(pathToSpriteFile);
       painter->drawPixmap(target, pixmap, source);
    }
}

QRectF SelectedVesselObjectSprite::boundingRect() const
{
    if(connectedVesselObject != nullptr){
        return this->connectedVesselObject->boundingRect();
    }
    return QRectF(0,0,0,0);
}


void SelectedVesselObjectSprite::advance(int step){
    if(!step){
        return;
    }
    if(connectedVesselObject != nullptr){
        this->setPos(connectedVesselObject->pos());
        this->setRotation(connectedVesselObject->rotation());
    }

}


VesselObject * SelectedVesselObjectSprite::getSelected(){
    if(connectedVesselObject != nullptr){
        return connectedVesselObject;
    }
    return nullptr;
}

void SelectedVesselObjectSprite::setSelecorItem(VesselObject * item){
    connectedVesselObject = item;
}
