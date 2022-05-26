#include "objectplacementsprite.h"
#include <QKeyEvent>
#include <src/graphics/gridsection.h>

VesselObjectPlacementSprite::VesselObjectPlacementSprite(Camera * toConnect, VesselObject *placingobj, Vessel * vessel)
{
    connectedCamera = toConnect;
    placementVesselObject = placingobj;
    connectedVessel = vessel;

    connectedCamera->scene()->addItem(this);
}

void VesselObjectPlacementSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if(placementVesselObject != nullptr){
       QRectF target = placementVesselObject->boundingRect();
       QRectF source = QRectF(0,0,placementVesselObject->boundingRect().width(),placementVesselObject->boundingRect().height());
       QPixmap pixmap(placementVesselObject->getSpriteFile());
       painter->drawPixmap(target, pixmap, source);
    }
}

QRectF VesselObjectPlacementSprite::boundingRect() const
{
    if(placementVesselObject != nullptr){
        return this->placementVesselObject->boundingRect();
    }
    return QRectF(0,0,0,0);
}


void VesselObjectPlacementSprite::advance(int step){
    if(!step){
        return;
    }
    if(placementVesselObject != nullptr && connectedVessel != nullptr){

        // The usual maptoscene displays placer with a small shift on x axis. I don't know how exactly this fixes the problem, but adding maptoglobal shifts it even more, so i subtracted it.
        QPointF cursorPosition =  connectedCamera->mapToScene(connectedCamera->cursor().pos()) +
                     (connectedCamera->mapToScene(connectedCamera->cursor().pos()) - connectedCamera->mapToScene(connectedCamera->mapToGlobal(connectedCamera->cursor().pos())));
        if(connectedVessel->getGrid() == nullptr){
            this->setPos(cursorPosition);
        }
        else{

        /*
            double smallestDistance = 2048 * 2048 + 1;
            GridSection * closestGrid = nullptr;
            for(auto grid : connectedVessel->getGrid()){
                double dx = (cursorPosition.x() - grid->pos().x());
                double dy = (cursorPosition.y() - grid->pos().y());
                //
                if(dx*dx + dy*dy< smallestDistance){
                    closestGrid = grid;
                    smallestDistance = dx*dx + dy*dy;
                }
            }
            if(closestGrid != nullptr){
                this->setPos(closestGrid->pos());
            }
            */
        }

        if(followVesselRotation){
            this->setRotation(placerRotation + connectedVessel->getRotation());
        }
        else{
            this->setRotation(placerRotation);
        }
    }
    else{
        delete this;
    }
}



void VesselObjectPlacementSprite::placeVesselObject(){
    if(placementVesselObject && connectedVessel){
        placementVesselObject->setVessel(connectedVessel);

        QPointF relCoordPoint = this->pos() - connectedVessel->getMassCenterCoords().toPointF() ;

        placementVesselObject->getRelativeCoordinates() = QVector2D(relCoordPoint.x(), relCoordPoint.y());
        placementVesselObject->setCoordinateRotation(connectedVessel->getRotation());

        placementVesselObject->setOwnRotation(placerRotation - connectedVessel->getRotation());

        if(followVesselRotation){
             placementVesselObject->setOwnRotation(placerRotation);
        }
        else{
             placementVesselObject->setOwnRotation(placerRotation - connectedVessel->getRotation());
        }

        connectedVessel->addVesselObject(placementVesselObject);
        connectedCamera->scene()->addItem(placementVesselObject);

        placementVesselObject->advance(1);

    }
}

void VesselObjectPlacementSprite::ChangeRotation(float rotationChange){
    placerRotation += rotationChange;
}

void VesselObjectPlacementSprite::switchVesselRotationFollowing(){
    followVesselRotation = !followVesselRotation;
}

bool VesselObjectPlacementSprite::getVesselRotationFollowing(){
    return followVesselRotation;
}

void VesselObjectPlacementSprite::onKeyPress(QKeyEvent *event, GameSettings *settings){
    if(event->key() == settings->getKeybinds()["RotLeftKey"]){
        ChangeRotation(-1);
    }
    if(event->key() == settings->getKeybinds()["RotRightKey"]){
        ChangeRotation(1);
    }
}

void VesselObjectPlacementSprite::onClick(QMouseEvent *, GameSettings *){
    placeVesselObject();
}
