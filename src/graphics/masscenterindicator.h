#ifndef MASSCENTERINDICATOR_H
#define MASSCENTERINDICATOR_H

#include <QGraphicsItem>
#include <src/object/vessel.h>

class MassCenterIndicator : public QGraphicsItem
{
    Vessel * connectedVessel = nullptr;

public:
    MassCenterIndicator(Vessel * connectedVessel);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;

};

#endif // MASSCENTERINDICATOR_H
