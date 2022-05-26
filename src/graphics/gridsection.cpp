#include "gridsection.h"
#include <src/graphics/grid.h>
#include <src/object/vesselobject.h>
#include <QPainter>

GridSection::GridSection(Grid * toConnect, QVector2D position)
{
    connectedGrid = toConnect;
    relativePosition = position;
    setOpacity(0.5);

}

GridSection::~GridSection(){

}

void GridSection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if((connectedGrid != nullptr) && connectedGrid->getGridAnchor() != nullptr){
        painter->setPen(QPen(QColor(0,0,0,60)));

        /*
        painter->drawRect(0,0,8,8);
        painter->drawRect(0,8,8,8);
        painter->drawRect(8,0,8,8);
        painter->drawRect(8,8,8,8);
        */


        painter->drawLine(-8,-8,8,-8);
        painter->drawLine(-8,0,8,0);
        painter->drawLine(-8,8,8,8);

        painter->drawLine(-8,-8,-8,8);
        painter->drawLine(0,-8,0,8);
        painter->drawLine(8,-8,8,8);

    }

}

QRectF GridSection::boundingRect() const
{

    return QRectF(-8,-8,16,16);
}

void GridSection::advance(int step){
    if(!step){
        return;
    }
    if(connectedGrid != nullptr){
        //
        QTransform rotationAroundCenter = QTransform();

            //rotate system of coordinates and get shifted position
            rotationAroundCenter.rotate(connectedGrid->getConnectedVessel()->getRotation() - rotation());
            rotationAroundCenter.translate(relativePosition.x(), relativePosition.y());

        //Get coordinates out of QTransform
        QPointF resultLocation = rotationAroundCenter.map(QPointF());
        relativePosition = QVector2D(resultLocation.x(), resultLocation.y());

        if(connectedGrid->getGridAnchor() != nullptr){
                this->setRotation(connectedGrid->getConnectedVessel()->getRotation());
                this->setPos(connectedGrid->getGridAnchor()->pos() + relativePosition.toPointF()    /*+connectedVessel->getGridConnectionPoint().toPointF()*/);
        //
        }
        else{
            this->setRotation(connectedGrid->getConnectedVessel()->getRotation());
            this->setPos(connectedGrid->getConnectedVessel()->getMassCenterCoords().toPointF() + relativePosition.toPointF());
        }
    }
}

QVector2D GridSection::getRelPosition(){
    return relativePosition;
}
