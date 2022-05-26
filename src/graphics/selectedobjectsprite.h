#ifndef SELECTEDOBJECTSPRITE_H
#define SELECTEDOBJECTSPRITE_H
#include <src/object/vesselobject.h>


class SelectedVesselObjectSprite : public QGraphicsItem
{
    QString pathToSpriteFile = "";

    VesselObject * connectedVesselObject = nullptr;


public:
    SelectedVesselObjectSprite(QString sprite, VesselObject * connectedVesselObject);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;


    VesselObject * getSelected();

    void setSelecorItem(VesselObject * item);

};


#endif // SELECTEDOBJECTSPRITE_H
