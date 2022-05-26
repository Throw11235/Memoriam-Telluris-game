#include "nbodyphysicssimulation.h"
#include <src/nbodysim/nbodysprites.h>





NBodyPhysicsSimulation::NBodyPhysicsSimulation(CelestialBody * mainBody, std::list<NBody*> & simulatedDynamicBodies){
    //The system is in a sqare 80 au across, twice the Pluto's semi major axis. More than enough for solar system.
    systemScene = new QGraphicsScene(-11967829656000,-11967829656000 ,23935659312000,23935659312000);
    systemScene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    systemView = new QGraphicsView(systemScene);

    systemCenterOfMass = mainBody;

    simulatedBodies = simulatedDynamicBodies;
}



void NBodyPhysicsSimulation::advanceSimulation(){
    systemCenterOfMass->OrbitalMotion(dt);

    for(auto body : simulatedBodies){
        body->moveSimBydt(dt, systemCenterOfMass);
    }
}

void NBodyPhysicsSimulation::addCelestial(CelestialBody * newCelestial){
    systemScene->addItem(newCelestial->getPlanetSprite());
    systemScene->addItem(newCelestial->getNameSprite());
}

void NBodyPhysicsSimulation::addNBody(NBody * newBody){
    simulatedBodies.push_back(newBody);

    systemScene->addItem(newBody->getSprite());

}

QGraphicsView * NBodyPhysicsSimulation::getSystemView(){
    return systemView;
}

void NBodyPhysicsSimulation::setTimeStep(double newDt){
    dt = newDt;
}
