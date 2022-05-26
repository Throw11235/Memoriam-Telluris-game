#include "vesselobjecttype.h"

VesselObjectType::VesselObjectType()
{

}

QString VesselObjectType::getSpriteFile(){
    return pathToSpriteFile;
}

float VesselObjectType::getHeight(){
    return objectHeight;
}

float VesselObjectType::getWidth(){
    return objectWidth;
}

float VesselObjectType::getBaseMass(){
    return mass;
}

void VesselObjectType::loadFromJson(nlohmann::json &loadedjson){
    try{
       typeName = loadedjson["Type_Name"];
       displayedName = QString::fromStdString(loadedjson["Displayed_Name"]);

       objectWidth = loadedjson["Width"];
       objectHeight = loadedjson["Heigth"];
       pathToSpriteFile = QString::fromStdString(loadedjson["Sprite"]);
       mass = loadedjson["BaseMass"];
    }
    catch(nlohmann::json::parse_error& ex){

    }
}

std::string VesselObjectType::getTypeName(){
    return typeName;
}

QString VesselObjectType::getDisplayedName(){
    return displayedName;
}
