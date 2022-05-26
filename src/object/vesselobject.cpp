#include "vesselobject.h"
#include <QPainter>
//#include <src/misc/vecorfunctions.h>

#include <cmath>

#define DEGREE_RADIAN_RATIO 57.2957795130823208768


VesselObject::VesselObject(QString spritePath, std::list<Interaction*> interractions, float width, float heigth, Vessel * refpoint, float x, float y, float mass)
{
    this->pathToSpriteFile = spritePath;
    this->interractionList = interractions;

    this->mass = mass;

    this->objectWidth = width;
    this->objectHeight = heigth;

    if(refpoint != nullptr){
        this->refPoint = refpoint;
        this->relativeCoordinates = QVector2D(x,y);
    }
    //it is assumed if reference point is null, create new vessel map
    else{
        this->refPoint = new Vessel(x, y, 0, 0, scene());
    }
}


void VesselObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->beginNativePainting();

    QRectF target(-this->objectWidth/2, -this->objectHeight/2, this->objectWidth, this->objectHeight);
    QRectF source(0, 0, this->objectWidth, this->objectHeight);
    QPixmap pixmap(pathToSpriteFile);
    painter->drawPixmap(target, pixmap, source);

    painter->endNativePainting();
}

void VesselObject::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event){
        //TBD
    }
}

void VesselObject::advance(int step){
    if(!step){
        return;
    }


    if(coordinateRotation == refPoint->getRotation()   && refPoint->getRotationSpeed() == 0){

        QVector2D newCoords = refPoint->getMassCenterCoords() + relativeCoordinates;
        setPos(newCoords.x(), newCoords.y());
    }
    else{ // If rotation is changed, calculate new relative coordinates

        QVector2D relCoordinates = this->relativeCoordinates;

        float angle =  refPoint->getRotation() - coordinateRotation;

        //if relative vector length is zero only need to change rotation. Also avoids divide by 0 situation.
        if(relCoordinates.x() != 0 || relCoordinates.y() != 0){
           // angle is the difference between expected position and actual position


            //Create a point containing initial relative coordinates of an object
            QPointF initialCoords = relCoordinates.toPointF();
            QTransform rotationAroundCenter = QTransform();

                //rotate system of coordinates and get shifted position
                rotationAroundCenter.rotate(angle);
                rotationAroundCenter.translate(initialCoords.x(), initialCoords.y());

            //Get coordinates out of QTransform
            QPointF resultLocation = rotationAroundCenter.map(QPointF());

            relCoordinates.setX(resultLocation.x());
            relCoordinates.setY(resultLocation.y());
        }
        //set new relative coordinates vector and set new position and rotation
        relativeCoordinates = relCoordinates;
        QVector2D newCoordinates = refPoint->getMassCenterCoords() + relativeCoordinates;

        setPos(newCoordinates.x(), newCoordinates.y());

        coordinateRotation = refPoint->getRotation();
        //make sure no overflow takes place
        if(coordinateRotation > 360){
            coordinateRotation -= 360;
        }
    }

    setRotation(coordinateRotation + objectRotation);

}


void VesselObject::UpdateObject(){
    //TBD
}

QRectF VesselObject::boundingRect() const
{
    return QRectF(-objectWidth/2,-objectHeight/2,objectWidth,objectHeight);
}

QPainterPath VesselObject::shape() const
{
    QPainterPath path;
    path.addRect(-objectWidth/2,-objectHeight/2,objectWidth,objectHeight);
    return path;
}


void VesselObject::rotateClockwise(float relRotation){
    objectRotation += relRotation;
  //  relativeCoordinates = RotateVector(relativeCoordinates, relRotation);
  //  baseRelativeCoords = RotateVector(baseRelativeCoords, relRotation);
}


QString VesselObject::getSpriteFile(){
    return pathToSpriteFile;
}

QVector2D &  VesselObject::getRelativeCoordinates(){
    return relativeCoordinates;
}

float VesselObject::getMass(){
    return mass;
}

float VesselObject::getRotation(){
    return coordinateRotation;
}

Vessel * VesselObject::getVessel(){
    return refPoint;
}

float VesselObject::getOwnRotation(){
    return objectRotation;
}

int VesselObject::type() const
{
    return OBJECT_TYPE;
}


nlohmann::json VesselObject::loadToJson(){
    nlohmann::json jsonVesselObject;
//    jsonVesselObject["Type"] = "Undefined_Type";
    jsonVesselObject["Width"] = objectWidth;
    jsonVesselObject["Heigth"] = objectHeight;
    jsonVesselObject["Sprite"] = pathToSpriteFile.toStdString();
    jsonVesselObject["Mass"] = mass;

    jsonVesselObject["XCoord"] = relativeCoordinates.x();
    jsonVesselObject["YCoord"] = relativeCoordinates.y();
    jsonVesselObject["Coordinate_Rotation"] = coordinateRotation;
    jsonVesselObject["Own_Rotation"] = objectRotation;

    return jsonVesselObject;
}

void VesselObject::loadFromJSON(nlohmann::json & loadedjson, std::map<std::string ,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions){
    try{
        //if type field is present, load static properties from it
        if(loadedjson.contains("Object_Type")){
            std::string ObjectTypeName = loadedjson["Object_Type"];
            //check if this type exists, if not, abort and throw an exeption

           if(objecttypes.find(ObjectTypeName) != objecttypes.end()){
               this->loadPropertiesFromType(objecttypes.find(ObjectTypeName)->second);
           }
           else{
               throw ObjectTypeName + " object template cannot be found";
           }
        }
        else{
            objectWidth = loadedjson["Width"];
            objectHeight = loadedjson["Heigth"];
            pathToSpriteFile = QString::fromStdString(loadedjson["Sprite"]);
        }

        mass = loadedjson["Mass"];
        relativeCoordinates = QVector2D(loadedjson["XCoord"], loadedjson["YCoord"]);
        objectRotation = loadedjson["Own_Rotation"];
        coordinateRotation = loadedjson["Coordinate_Rotation"];
    }
    catch(nlohmann::json::parse_error& ex){
        exeptions.push_back(ex.what());
    }
    catch (std::string & exstr) {
        exeptions.push_back(exstr);
    }
}

VesselObject::VesselObject(nlohmann::json & json, Vessel * boundVessel, std::map<std::string ,VesselObjectType*> & objecttypes, std::list<std::string> & exeptions){

    if(boundVessel != nullptr){
        refPoint = boundVessel;

        this->loadFromJSON(json, objecttypes, exeptions);
    }
    else{
        delete this;
    }
}

void VesselObject::setVessel(Vessel *newVessel){
    refPoint = newVessel;
}

void VesselObject::setCoordinateRotation(float newRotation){
    coordinateRotation = newRotation;
}

void VesselObject::setOwnRotation(float newRotation){
    objectRotation = newRotation;
}

void VesselObject::loadPropertiesFromType(VesselObjectType *type){
    // static properties what are not supposed to be changed
    pathToSpriteFile = type->getSpriteFile();
    objectHeight = type->getHeight();
    objectWidth = type->getWidth();

    //base values of the non static properties
    mass = type->getBaseMass();
}


