#ifndef NBODY2D_H
#define NBODY2D_H
#include <QVector2D>
#include <QGraphicsObject>
#include <src/nbodysim/celestialbody2d.h>

class NBodySprite;

class NBody : public QGraphicsItem
{
    QVector2D velocity = QVector2D(0,0);
    QPointF mapCoords = QPointF(0,0);

    float mass;

    NBodySprite * connectedSprite = nullptr;

    // force that affected body at last simulation tick, used for said n-body simulation
    QVector2D prevForce = QVector2D(0,0);
public:
    NBody(QPointF coords, float startingmass,  QVector2D startingvelocity = QVector2D(0,0));

    void setVelocity(QVector2D newVel);
    void setMass(float newMass);

    QVector2D getVelocity();
    QVector2D getPrevForce();

    float getMass();
    float getTimeStep();

    void moveSimBydt(float dt, CelestialBody * systemAnchor);

    void advance(int step);

    NBodySprite * getSprite();
};

#endif // NBODY2D_H
