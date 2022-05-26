#ifndef VESSEL_H
#define VESSEL_H
#include <QVector2D>
#include <QObject>
#include <QGraphicsScene>
#include <nlohmann/json.hpp>

class VesselObjectType;

class VesselObject;

class Grid;

class Vessel : public QObject
{
    QVector2D pointGlobalCoords = QVector2D(0,0);
    QVector2D centerOfMassCoords = QVector2D(0,0);

    QVector2D gridConnectionPoint = QVector2D(0,0);

    QVector2D lastCoordChange = QVector2D(0,0);

    QVector2D speed = QVector2D(0,0);
    float rotationSpeed = 0.0;

    float rotation = 0.0;
    float mass = 0.0;
    float momentOfInertia = 0.0;

    QGraphicsScene * scene = nullptr;

    std::list<VesselObject *> objectsOnVessel = {};

    Grid *  activeGrid = nullptr;

public:
    Vessel(float x, float y, float mass, float rotation, QGraphicsScene * startingScene);

    QVector2D getGlobalCoords();
    QVector2D getMassCenterCoords();

    QVector2D getGridConnectionPoint();
    QVector2D getLastCoordinateChange();

    float getRotation();
    float getMass();


    void deployGrid();
    void destroyGrid();
    Grid * getGrid();


    float getRotationSpeed();
    QVector2D getSpeed();
    std::list<VesselObject *> & getVesselObjects();

    void setMass(float newMass);
    void setRotation(float newRotation);
    void setNewCoords(QVector2D newCoords);
    void setNewCenterOfMass(QVector2D newCoords);
    void setSpeed(QVector2D newSpeed);
    void setRotationSpeed(float newRotSpeed);



    void addVesselObject(VesselObject * toAdd);
    void addVesselObjectList(std::list <VesselObject *> & toAdd);
    void removeVesselObject(VesselObject * toRemove);

    void applyImpulse(QVector2D & relativePosition, QVector2D & impulse);

    void collide(VesselObject * ownVesselColliding,   VesselObject * anotherVesselColliding);

    void move(float timeStep);

    void loadFromJson(nlohmann::json & vesseljson, QGraphicsScene * scene, std::map<std::string ,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions);

    nlohmann::json loadToJson();
};

#endif // VESSEL_H
