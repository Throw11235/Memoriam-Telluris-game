#include "vessel.h"
#include "vesselobject.h"
#include <QTransform>
#include <src/graphics/gridsection.h>

QVector2D RotVector(QVector2D  toRotate, float angle){
    //Convert vector to a point with same coordinates
    QPointF initialCoords = toRotate.toPointF();

    QTransform rotationAroundCenter = QTransform();

        //rotate system of coordinates and get shifted position
        rotationAroundCenter.rotate(-angle);
        rotationAroundCenter.translate(initialCoords.x(), initialCoords.y());

    //Get coordinates out of QTransform
    QPointF resultVectorCoords = rotationAroundCenter.map(QPointF());

    return QVector2D(resultVectorCoords.x(), resultVectorCoords.y());
}

Vessel::Vessel(float x, float y, float mass, float rotation, QGraphicsScene * startingScene)
{
    QVector2D globalCoords(x,y);
    this->pointGlobalCoords = globalCoords;
    this->centerOfMassCoords = QVector2D(0,0);
    this->mass = mass;
    this->rotation = rotation;
    this->scene = startingScene;
}


QVector2D Vessel::getGlobalCoords(){
    return pointGlobalCoords;
}

QVector2D Vessel::getMassCenterCoords(){
    return pointGlobalCoords + centerOfMassCoords;
}


float Vessel::getRotation(){
    return rotation;
}

std::list<VesselObject *> & Vessel::getVesselObjects(){
    return objectsOnVessel;
}

float Vessel::getMass(){
    return mass;
}

float Vessel::getRotationSpeed(){
    return rotationSpeed;
}

QVector2D Vessel::getSpeed(){
    return speed;
}


QVector2D  Vessel::getLastCoordinateChange(){
    return lastCoordChange;
}


void Vessel::setNewCoords(QVector2D newCoords){
    pointGlobalCoords = newCoords;
}

void Vessel::setNewCenterOfMass(QVector2D newCoords){
    centerOfMassCoords = newCoords;
}


void Vessel::setMass(float newMass){
    mass = newMass;
}

void Vessel::setRotation(float newRotation){
    rotation = newRotation;
}

void Vessel::setSpeed(QVector2D newSpeed){
    speed = newSpeed;
}

void Vessel::setRotationSpeed(float newRotSpeed){
    rotationSpeed = newRotSpeed;
}

void Vessel::move(float timeStep){
    pointGlobalCoords += speed * timeStep;
    rotation += rotationSpeed * timeStep;
    lastCoordChange = speed * timeStep;

    //make sure no overflow takes place
    if(rotation > 360){
        rotation -= 360;
    }

}


void Vessel::addVesselObject(VesselObject *toAdd){
    objectsOnVessel.push_back(toAdd);
    if(this->mass != 0){
        QVector2D coordinateChange= (toAdd->getRelativeCoordinates() - centerOfMassCoords) * (toAdd->getMass()/ this->mass);
        centerOfMassCoords += coordinateChange;

      for(auto obj : objectsOnVessel){
            obj->getRelativeCoordinates() -= coordinateChange;
      }
      gridConnectionPoint -= coordinateChange;

    }
    else{
        centerOfMassCoords = toAdd->getRelativeCoordinates();
        toAdd->getRelativeCoordinates() = QVector2D(0,0);
    }
    this->mass += toAdd->getMass();
    this->momentOfInertia += toAdd->getMass() * toAdd->getRelativeCoordinates().lengthSquared();
}

void Vessel::removeVesselObject(VesselObject *toRemove){
    mass -= toRemove->getMass();
    momentOfInertia -= toRemove->getMass() * toRemove->getRelativeCoordinates().lengthSquared();

    QVector2D coordinateChange = toRemove->getRelativeCoordinates() * (toRemove->getMass() / this->getMass());
    centerOfMassCoords -= coordinateChange;
    for(auto obj : objectsOnVessel){
        obj->getRelativeCoordinates() += coordinateChange;
    }
    gridConnectionPoint += coordinateChange;

    objectsOnVessel.remove(toRemove);
}

void Vessel::addVesselObjectList(std::list<VesselObject *> & toAdd){
    float totalMass = 0.0;
    QVector2D totalChange = QVector2D(0,0);
    float totalInertia = 0.0;

    for(auto object : toAdd){
        objectsOnVessel.push_back(object);
        totalMass += object->getMass();
        totalChange += object->getRelativeCoordinates() * object->getMass();
        totalInertia += object->getMass() * object->getRelativeCoordinates().lengthSquared();

    }
    totalChange /= totalMass;
    if(this->mass != 0){
        mass += totalMass;
        momentOfInertia += totalInertia;
        centerOfMassCoords += totalChange;
        for(auto object : objectsOnVessel){
            object->getRelativeCoordinates() -= totalChange;
        }
        gridConnectionPoint -= totalChange;
    }
    else{
        mass = totalMass;
        centerOfMassCoords = totalChange;
        gridConnectionPoint = QVector2D(0,0);
        momentOfInertia = totalInertia;
    }
}

void unelasticCollision(VesselObject *ownVesselColliding, VesselObject *anotherVesselColliding){
    std::list<VesselObject *> collisionpoints = {};
   // for(auto object : ownVesselColliding->getVessel() objectsOnVessel){
   //
   // }

    //if only one collision point
    if(collisionpoints.size() == 0){
        QVector2D ownVelocity = ownVesselColliding->getVessel()->getSpeed() ;
        QVector2D collidingVelocity = anotherVesselColliding->getVessel()->getSpeed();

        QVector2D resultingVelocity = (ownVesselColliding->getVessel()->getMass() * ownVelocity + anotherVesselColliding->getVessel()->getMass() * collidingVelocity) / (ownVesselColliding->getVessel()->getMass() + anotherVesselColliding->getVessel()->getMass());

        ownVesselColliding->getVessel()->setSpeed(resultingVelocity);
        anotherVesselColliding->getVessel()->setSpeed(resultingVelocity);
    }
    else{
        collisionpoints.push_back(ownVesselColliding);
    }

}

void elasticCollision(VesselObject *ownVesselColliding, VesselObject *anotherVesselColliding){
    std::list<VesselObject *> collisionpoints = {};
   // for(auto object : ownVesselColliding->getVessel() objectsOnVessel){
   //
   // }

    //if only one collision point
    if(collisionpoints.size() == 0){
        QVector2D ownVelocity = ownVesselColliding->getVessel()->getSpeed() ;
        QVector2D collidingVelocity = anotherVesselColliding->getVessel()->getSpeed();

        QVector2D resultingVelocity = (ownVesselColliding->getVessel()->getMass() * ownVelocity + anotherVesselColliding->getVessel()->getMass() * collidingVelocity) / (ownVesselColliding->getVessel()->getMass() + anotherVesselColliding->getVessel()->getMass());

        ownVesselColliding->getVessel()->setSpeed(resultingVelocity);
        anotherVesselColliding->getVessel()->setSpeed(resultingVelocity);
    }
    else{
        collisionpoints.push_back(ownVesselColliding);
    }
}

void splashCollision(VesselObject *ownVesselColliding, VesselObject *anotherVesselColliding){
    std::list<VesselObject *> collisionpoints = {};
   // for(auto object : ownVesselColliding->getVessel() objectsOnVessel){
   //
   // }

    //if only one collision point
    if(collisionpoints.size() == 0){
        QVector2D ownVelocity = ownVesselColliding->getVessel()->getSpeed() ;
        QVector2D collidingVelocity = anotherVesselColliding->getVessel()->getSpeed();

        QVector2D resultingVelocity = (ownVesselColliding->getVessel()->getMass() * ownVelocity + anotherVesselColliding->getVessel()->getMass() * collidingVelocity) / (ownVesselColliding->getVessel()->getMass() + anotherVesselColliding->getVessel()->getMass());

        ownVesselColliding->getVessel()->setSpeed(resultingVelocity);
        anotherVesselColliding->getVessel()->setSpeed(resultingVelocity);
    }
    else{
        collisionpoints.push_back(ownVesselColliding);
    }
}

void Vessel::collide(VesselObject *ownVesselColliding, VesselObject *anotherVesselColliding){
    QVector2D relspeed = ownVesselColliding->getVessel()->getSpeed() - anotherVesselColliding->getVessel()->getSpeed();
    if(relspeed.length() > 10){
        elasticCollision(ownVesselColliding, anotherVesselColliding);
    }
    else{
        unelasticCollision(ownVesselColliding, anotherVesselColliding);
    }
}

void Vessel::loadFromJson(nlohmann::json &vesseljson, QGraphicsScene * scene, std::map<std::string ,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions){
    try{
        //load objects on vessel
        for(const auto & embeddedVesselObject : vesseljson["VesselObjects"]){
            VesselObject * newObj = nullptr;
            try{
                nlohmann::json objectjson = embeddedVesselObject;
                std::string typevalue = objectjson["Type"];
                newObj = new VesselObject(objectjson, this, objecttypes, exeptions);
                scene->addItem(newObj);
                newObj->advance(1);
                this->objectsOnVessel.push_back(newObj);
            }
            catch(nlohmann::json::parse_error& ex){

            }
        }


        mass = vesseljson["Mass"];
        rotation =  vesseljson["Rotation"];
        rotationSpeed = vesseljson["RotSpeed"];
        momentOfInertia = vesseljson["InertiaMoment"];
        speed = QVector2D(vesseljson["XVel"], vesseljson["YVel"]);
        pointGlobalCoords = QVector2D(vesseljson["XPos"], vesseljson["YPos"]);
        centerOfMassCoords = QVector2D(vesseljson["XMassCoords"], vesseljson["YMassCoords"]);
    }
    catch(nlohmann::json::parse_error& ex){

    }
}

nlohmann::json Vessel::loadToJson(){
    nlohmann::json vesselJson;
    vesselJson["Mass"] = mass;
    vesselJson["XVel"] = speed.x();
    vesselJson["YVel"] = speed.y();
    vesselJson["XPos"] = pointGlobalCoords.x();
    vesselJson["YPos"] = pointGlobalCoords.y();
    vesselJson["XMassCoords"] = centerOfMassCoords.x();
    vesselJson["YMassCoords"] = centerOfMassCoords.y();

    vesselJson["Rotation"] = rotation;
    vesselJson["RotSpeed"] = rotationSpeed;
    vesselJson["InertiaMoment"] = momentOfInertia;


    std::list<nlohmann::json> objs = {};
    for(VesselObject * obj : objectsOnVessel){
        objs.push_back(obj->loadToJson());
    }
    vesselJson["VesselObjects"] = objs;

    return vesselJson;
}

Grid * Vessel::getGrid(){
    return activeGrid;
}

QVector2D Vessel::getGridConnectionPoint(){
    return RotVector( gridConnectionPoint, rotation);
}


void Vessel::applyImpulse(QVector2D &relativePosition, QVector2D & impulse){
    double cosin = QVector2D::dotProduct(relativePosition, impulse) / (relativePosition.length() * impulse.length());
    double sin = std::sqrt(1 - cosin * cosin);

    QVector2D speedchange =-1 * relativePosition * (impulse.length() * cosin /relativePosition.length()) / mass;
    speed += speedchange;

    double rotationchange = impulse.length() * sin * relativePosition.length() / momentOfInertia;
    rotationSpeed += rotationchange;
}
