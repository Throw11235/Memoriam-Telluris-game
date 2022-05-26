#ifndef INBODYPHYSICSSIMULATION_H
#define INBODYPHYSICSSIMULATION_H

#include <QGraphicsView>

#include <src/nbodysim/nbody2d.h>
#include <src/nbodysim/celestialbody2d.h>




class NBodyPhysicsSimulation : public QObject
{
    std::list<NBody*> simulatedBodies = {};
    CelestialBody * systemCenterOfMass = nullptr;

    QGraphicsView * systemView = nullptr;

    QGraphicsScene * systemScene;

    double dt = 0.0;
public:
    NBodyPhysicsSimulation(CelestialBody * mainBody, std::list<NBody*> & simulatedDynamicBodies);
    void advanceSimulation();

    void addCelestial(CelestialBody * newCelestial);
    void addNBody(NBody * newBody);

    void setTimeStep(double newdt);

    QGraphicsView * getSystemView();
};

#endif // INBODYPHYSICSSIMULATION_H
