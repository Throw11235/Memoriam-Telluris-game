#ifndef OBJECTPLACEMENTFACTORYBUTTON_H
#define OBJECTPLACEMENTFACTORYBUTTON_H
#include <QPushButton>
#include <src/graphics/camera.h>

class VesselObjectPlacerButtonLink : public QObject
{
    Camera * connectedCamera = nullptr;
    QString pathToSpriteFile = "";
    float objectWidth = 0.0;
    float objectHeight = 0.0;
    float objectMass = 0.0;

public:
    VesselObjectPlacerButtonLink(QString spritefile, float width, float height, float mass, Camera * toConnect);
    ~VesselObjectPlacerButtonLink();

    void setPlacer();
};



class VesselObjectPlacementFactoryButton : public QPushButton
{
    QString pathToSpriteFile = "";

    VesselObjectPlacerButtonLink * slotLink = nullptr;
public:
    VesselObjectPlacementFactoryButton(QString spritefile, float x, float y, float width, float height, float mass, Camera * toConnect);
};

#endif // OBJECTPLACEMENTFACTORYBUTTON_H
