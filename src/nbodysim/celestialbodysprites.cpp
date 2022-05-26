#include "celestialbodysprites.h"
#include <QPainter>
#include <src/nbodysim/celestialbody2d.h>

#define KM_TO_OVERMAP_DIST_UNITS 1000

CelestialBodySprite::CelestialBodySprite(QColor color, CelestialBody * toConnect)
{
    planetColor = color;
    connectedBody = toConnect;
}


void CelestialBodySprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->beginNativePainting();

    painter->drawEllipse(connectedBody->getFullCoords(),connectedBody->getRadius() * 2, connectedBody->getRadius() * 2);

    painter->endNativePainting();
}

QRectF CelestialBodySprite::boundingRect() const
{

    return QRectF(-1 * connectedBody->getRadius(), -1 * connectedBody->getRadius(), 2 * connectedBody->getRadius(), 2 * connectedBody->getRadius());
}

void CelestialBodySprite::advance(int step){
    if(!step){
        return;
    }
    setPos(connectedBody->getFullCoords());
}




CelestialBodyNameSprite::CelestialBodyNameSprite(QString name, CelestialBody * toConnect){
    planetName = name;
    connectedBody = toConnect;
}

void CelestialBodyNameSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->beginNativePainting();

    painter->drawEllipse(connectedBody->getFullCoords(),connectedBody->getRadius() * 2, connectedBody->getRadius() * 2);

    painter->endNativePainting();
}

QRectF CelestialBodyNameSprite::boundingRect() const
{

    return QRectF(-1 * connectedBody->getRadius(), -1 * connectedBody->getRadius(), 2 * connectedBody->getRadius(), 2 * connectedBody->getRadius());
}

void CelestialBodyNameSprite::advance(int step){
    if(!step){
        return;
    }
    setPos(connectedBody->getFullCoords());
}
