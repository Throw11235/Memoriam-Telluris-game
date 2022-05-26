#ifndef CELESTIALBODYSPRITES_H
#define CELESTIALBODYSPRITES_H
#include <QGraphicsItem>

class CelestialBody;

class CelestialBodySprite : public QGraphicsItem
{
    QColor planetColor = QColor();
    CelestialBody * connectedBody = nullptr;
public:
    CelestialBodySprite(QColor color, CelestialBody * toConnect);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;
};

class CelestialBodyNameSprite : public QGraphicsItem
{
    QString planetName = "";
    CelestialBody * connectedBody = nullptr;
public:
    CelestialBodyNameSprite(QString name, CelestialBody * toConnect);

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;
};


#endif // CELESTIALBODYSPRITES_H
