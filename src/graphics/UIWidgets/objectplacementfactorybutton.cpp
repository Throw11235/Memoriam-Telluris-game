#include "objectplacementfactorybutton.h"
#include <src/graphics/objectplacementsprite.h>

VesselObjectPlacerButtonLink::VesselObjectPlacerButtonLink(QString spritefile, float width, float height, float mass, Camera * toConnect){
    connectedCamera = toConnect;
    objectHeight = height;
    objectMass = mass;
    objectWidth = width;
    pathToSpriteFile = spritefile;

}

VesselObjectPlacerButtonLink::~VesselObjectPlacerButtonLink(){

}

void VesselObjectPlacerButtonLink::setPlacer(){
    connectedCamera->setPlacer(new VesselObjectPlacementSprite(connectedCamera, new VesselObject(pathToSpriteFile,{},objectWidth,objectHeight, nullptr ,0,0,objectMass), connectedCamera->getVessel()));
}

VesselObjectPlacementFactoryButton::VesselObjectPlacementFactoryButton(QString spritefile, float x, float y, float width, float height, float mass, Camera * toConnect)
{
    this->setGeometry(x,y,50, 50);

    this->setStyleSheet("background-color: rgba(100, 100, 100, 100); border-color: rgba(100, 100, 100, 100);");

    this->slotLink = new VesselObjectPlacerButtonLink(spritefile, width, height, mass, toConnect);
    this->setIcon(QIcon(spritefile));
    QObject::connect(this, &QPushButton::pressed, this->slotLink, &VesselObjectPlacerButtonLink::setPlacer);
}
