#include "celestialbody2d.h"
#include <cmath>
#include <src/misc/vectorfunctions.h>

CelestialBody::CelestialBody(CelestialBody * parent, QVector2D newRelativeCoords, QVector2D newRelativeSpeed)
{
    parentBody = parent;

    relativeCoords = newRelativeCoords;
    relativeVelocity = newRelativeSpeed;

    planetSprite = new CelestialBodySprite(Qt::green, this);
    nameSprite = new CelestialBodyNameSprite("ETH",this);
}

QVector2D CelestialBody::getGravityInAPoint(QPointF point){
    QVector2D rangeVector = QVector2D(point - absoluteCoords);

    QVector2D gravVector = (rangeVector / rangeVector.length()) * MassGravConstant/rangeVector.lengthSquared();
    for(auto iter : this->childbodies){
        gravVector = gravVector + iter->getGravityInAPoint(point);
    }
    return gravVector;
}

void CelestialBody::OrbitalMotion(double dt){
    if(parentBody != nullptr){


        double distance = relativeCoords.lengthSquared();

        QVector2D gravityPull = -1 * relativeCoords / (relativeCoords.length() * distance) * parentBody->MassGravConstant;

        QVector2D oldVelocity = relativeVelocity;
        relativeVelocity += gravityPull * dt;

        QVector2D coordchange = (relativeVelocity + oldVelocity) / 2 * dt;

        relativeCoords += coordchange;

        for(CelestialBody * child : childbodies){
            child->getRelativeCoords() + coordchange;

            child->OrbitalMotion(dt);
        }

        absoluteCoords = parentBody->getFullCoords() + relativeCoords.toPointF();
    }
    else{
        absoluteCoords = QPointF(0,0);
    }
}

QVector2D & CelestialBody::getRelativeCoords(){
    return relativeCoords;
}

QPointF & CelestialBody::getFullCoords(){
    return absoluteCoords;
}



double CelestialBody::getRadius(){
    return CelestialRadius;
}

CelestialBodySprite * CelestialBody::getPlanetSprite(){
    return planetSprite;
}

CelestialBodyNameSprite * CelestialBody::getNameSprite(){
    return nameSprite;
}
