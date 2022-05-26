#ifndef VESSELOBJECTTYPE_H
#define VESSELOBJECTTYPE_H
#include <QString>
#include <nlohmann/json.hpp>

class VesselObjectType
{
private:
    //Name by which game identifies type of an object
    std::string typeName = "";

    //Name which is displayed for the player
    QString displayedName = "";

    float mass = 0.0;

    float objectWidth = 0.0;
    float objectHeight = 0.0;

    QString pathToSpriteFile = "";

 // std::list<Interaction*> interractionList = {};

public:
    VesselObjectType();

    QString getSpriteFile();

    float getHeight();

    float getWidth();

    float getBaseMass();

    std::string getTypeName();

    QString getDisplayedName();

    void loadFromJson(nlohmann::json & loadedjson);
};

#endif // VESSELOBJECTTYPE_H
