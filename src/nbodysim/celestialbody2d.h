#ifndef CELESTIALBODY2D_H
#define CELESTIALBODY2D_H
#include <QVector2D>
#include <QGraphicsItem>
#include <src/nbodysim/celestialbodysprites.h>

class CelestialBody
{
 //   bool hidden = false;

    QVector2D relativeCoords = QVector2D(0,0);
    QVector2D relativeVelocity = QVector2D(0,0);

    QPointF absoluteCoords = QPointF(0,0);
    //Mass multiplied by G constant to optimize  the simulation
    double MassGravConstant = 0;



    double CelestialRadius = 0;

    //list of Celestial bodies that orbit the main body

    CelestialBody * parentBody = nullptr;

    std::list<CelestialBody*> childbodies = {};

    CelestialBodySprite * planetSprite = nullptr;
    CelestialBodyNameSprite * nameSprite = nullptr;


public:

    QVector2D getGravityInAPoint(QPointF point);
    void OrbitalMotion(double dt);
    CelestialBody(CelestialBody * parent, QVector2D relativeCoords, QVector2D relativeSpeed);

    QVector2D & getRelativeCoords();
    QPointF & getFullCoords();
    double getRadius();

    CelestialBodySprite * getPlanetSprite();
    CelestialBodyNameSprite * getNameSprite();
};

#endif // CELESTIALBODY2D_H
