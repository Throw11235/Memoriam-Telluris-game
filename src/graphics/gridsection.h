#ifndef GRIDSECTION_H
#define GRIDSECTION_H
#include <QGraphicsItem>
#include <src/object/vessel.h>

class Grid;



class GridSection : public QGraphicsItem
{
    QVector2D relativePosition = QVector2D(0,0);

    Grid * connectedGrid = nullptr;
public:
    GridSection(Grid * toConnect, QVector2D position);
    ~GridSection();

    void advance(int step) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRectF boundingRect() const override;

    QVector2D getRelPosition();

};

#endif // GRIDSECTION_H
