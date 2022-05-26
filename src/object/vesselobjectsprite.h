#ifndef VESSELOBJECTSPRITE_H
#define VESSELOBJECTSPRITE_H

#include <QGraphicsItem>

class VesselObject;

class VesselObjectSprite : public QGraphicsItem
{
    QRectF spriteRectangle = QRectF(0,0,0,0);
    QString pathToSpriteFile = "";

    VesselObject * connectedObject = nullptr;

public:
    VesselObjectSprite(QRectF sRect, QString sprite, VesselObject * toConnect);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;
};

#endif // VESSELOBJECTSPRITE_H
