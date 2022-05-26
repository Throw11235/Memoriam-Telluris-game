#ifndef CAMERA_H
#define CAMERA_H
#include <QGraphicsView>
#include <src/object/interraction/interaction.h>
#include <src/graphics/selectedobjectsprite.h>
#include <src/gamesettings.h>
#include <src/uimanager.h>

class VesselObjectPlacementSprite;

class Camera : public QGraphicsView
{
    UImanager * interfaceManager = nullptr;


    QPointF coords;

    float angle = 0.0;

    QGraphicsItem * followingItem = nullptr;

    std::list<Interaction*> activeInterractions = {};

    SelectedVesselObjectSprite * selector = nullptr;

    VesselObjectPlacementSprite * placer = nullptr;

    Vessel * followingVessel = nullptr;

    GameSettings * settings = nullptr;

public:
    Camera(UImanager * toConnect);

    float getAngle();

    void setPlacer(VesselObjectPlacementSprite * newplacer);

    void setSettings(GameSettings * newSettings);

    void keyPressEvent(QKeyEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    Vessel * getVessel();


    void  mousePressEvent(QMouseEvent *event) override;

    void  mouseDoubleClickEvent(QMouseEvent *event) override;


    void updateCameraPosition();

};

#endif // CAMERA_H
