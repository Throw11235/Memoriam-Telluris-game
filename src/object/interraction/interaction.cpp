#include "interaction.h"

Interaction::Interaction(VesselObject * obj, QString name)
{
    this->interractableVesselObject = obj;
    this->name = name;
}


void Interaction::setNewName(QString newName){
    this->name = newName;
}

void Interaction::setNewVesselObject(VesselObject *obj){
    this->interractableVesselObject = obj;
}


QString Interaction::getInterractionName(){
    return name;
}

VesselObject * Interaction::getVesselObject(){
    return interractableVesselObject;
}


void Interaction::Interract(){} // placeholder for inheritor classes to override
