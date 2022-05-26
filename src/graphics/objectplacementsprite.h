#ifndef OBJECTPLACEMENTSPRITE_H
#define OBJECTPLACEMENTSPRITE_H
#include <src/graphics/camera.h>


class VesselObjectPlacementSprite : public QGraphicsItem
{
    Camera * connectedCamera = nullptr;
    VesselObject * placementVesselObject = nullptr;
    Vessel * connectedVessel = nullptr;

    float placerRotation = 0.0;

    bool followVesselRotation = true;

public:
    VesselObjectPlacementSprite(Camera * toConnect, VesselObject * placingVesselObject, Vessel * vessel);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;

    void ChangeRotation(float rotationChange);

    void placeVesselObject();

    void switchVesselRotationFollowing();

    bool getVesselRotationFollowing();

    void onKeyPress(QKeyEvent * event, GameSettings * settings);

    void onClick(QMouseEvent * event, GameSettings * settings);
};

#endif // OBJECTPLACEMENTSPRITE_H
