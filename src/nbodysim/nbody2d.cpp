#include "nbody2d.h"
#include <src/nbodysim/nbodysprites.h>

#define MILISEC_TO_SEC 0.001

NBody::NBody(QPointF coords, float startingmass,  QVector2D startingvelocity)
{
    mapCoords = coords;
    mass = startingmass;
    velocity = startingvelocity;

    connectedSprite = new NBodySprite(this, "");
}


void NBody::setVelocity(QVector2D newVel){
    velocity = newVel;
}

void NBody::setMass(float newMass){
    mass = newMass;
}




QVector2D NBody::getPrevForce(){
    return prevForce;
}


QVector2D NBody::getVelocity(){
    return velocity;
}

float NBody::getMass(){
    return mass;
}





void NBody::advance(int step){
    if(!step){
        return;
    }

}

void NBody::moveSimBydt(float dt, CelestialBody * systemAnchor){
    QVector2D gravforce = systemAnchor->getGravityInAPoint(mapCoords);
    QVector2D totalForce = (prevForce + gravforce) / 2;

    QVector2D oldVelocity = velocity;
    velocity += totalForce * dt;

    mapCoords += ((oldVelocity + velocity)/2 * dt).toPointF();

    prevForce = gravforce;
}

NBodySprite * NBody::getSprite(){
    return connectedSprite;
}
