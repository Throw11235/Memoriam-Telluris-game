#ifndef NBODYSPRITES_H
#define NBODYSPRITES_H

#include <QGraphicsItem>
#include <src/nbodysim/nbody2d.h>

class NBodySprite : public QGraphicsItem
{

    NBody * connectedBody = nullptr;

    QString pathToSpriteFile = "";
public:
    NBodySprite(NBody * toConnect, QString sprite);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;
};

#endif // NBODYSPRITES_H
