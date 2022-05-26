#include "camera.h"
#include <QKeyEvent>
#include <QTransform>
#include <QLabel>
#include <src/graphics/objectplacementsprite.h>
#include <fstream>
#include <iostream>
#include <src/misc/vectorfunctions.h>


Camera::Camera(UImanager * toConnect)
{
    interfaceManager = toConnect;

    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    coords = QPointF(0,0);
}


void Camera::keyPressEvent(QKeyEvent *event){
    //Here was supposed to be a switch statement, and when  keys was hard-set it was
    //but since in  c++17 switch statement only deals with const integers defined at compile time, i had to change that
    //So here it is, a tower of continious ifs. At least it is only executed when user presses a button.

    if(event->key() == settings->getKeybinds()["ForwardKey"]){

        if(scene()){
            this->followingItem = nullptr;

            QVector2D moveVector = QVector2D(0, - 10);
            /*
            QTransform rotateMoveVector = QTransform();

           rotateMoveVector.rotate(angle);
            rotateMoveVector.translate(moveVector.x(), moveVector.y());

            */

            QVector2D resultingShift = RotateVector(moveVector, angle);


            coords.setX(coords.x() + resultingShift.x());
            coords.setY(coords.y() + resultingShift.y());
            this->centerOn(coords);
        }

    }

    else if(event->key() == settings->getKeybinds()["BackKey"]){

        if(scene()){
            this->followingItem = nullptr;

            QVector2D moveVector = QVector2D(0, 10);
            /*
            QTransform rotateMoveVector = QTransform();

           rotateMoveVector.rotate(angle);
            rotateMoveVector.translate(moveVector.x(), moveVector.y());

            */

            QVector2D resultingShift = RotateVector(moveVector, angle);


            coords.setX(coords.x() + resultingShift.x());
            coords.setY(coords.y() + resultingShift.y());
            this->centerOn(coords);
        }

    }

    else if(event->key() == settings->getKeybinds()["LeftKey"]){

        if(scene()){
            this->followingItem = nullptr;

            QVector2D moveVector = QVector2D( - 10, 0);

            /*
            QTransform rotateMoveVector = QTransform();

           rotateMoveVector.rotate(angle);
            rotateMoveVector.translate(moveVector.x(), moveVector.y());

            */

            QVector2D resultingShift = RotateVector(moveVector, angle);


            coords.setX(coords.x() + resultingShift.x());
            coords.setY(coords.y() + resultingShift.y());
            this->centerOn(coords);
        }

    }

    else if(event->key() == settings->getKeybinds()["RightKey"]){
        if(scene()){
            this->followingItem = nullptr;

            QVector2D moveVector = QVector2D(10, 0);
            /*
            QTransform rotateMoveVector = QTransform();

           rotateMoveVector.rotate(angle);
            rotateMoveVector.translate(moveVector.x(), moveVector.y());

            */

            QVector2D resultingShift = RotateVector(moveVector, angle);

            coords.setX(coords.x() + resultingShift.x());
            coords.setY(coords.y() + resultingShift.y());
            this->centerOn(coords);
        }

    }


    else if(event->key() == settings->getKeybinds()["RotRightKey"]){
        if(placer != nullptr){
            placer->ChangeRotation(-1);
        }
        else{
         this->rotate(+1);
         angle -= 1;
        }
    }
    else if(event->key() == settings->getKeybinds()["RotLeftKey"]){
            if(placer != nullptr){
                placer->ChangeRotation(1);
            }
            else{
             this->rotate(-1);
             angle += 1;
            }
    }


    else if(event->key() == settings->getKeybinds()["TempSaveKey"]){
            if(followingVessel){
                std::ofstream fwriter("/home/vitang/Dev/jsontest.json");
                fwriter << followingVessel->loadToJson();
                fwriter.close();
            }
    }


    else if(event->key() == Qt::Key::Key_Escape){
        if(interfaceManager->getInterfaceWidgets().size() > 0){
            interfaceManager->clearActiveInterface();
        }
        else{
            interfaceManager->showMenu();
        }
    }



}

void Camera::wheelEvent(QWheelEvent *event){
    QPoint zoom = event->angleDelta();

    qreal zoomFactor = 1 + zoom.y() / 300.0;
    scale(zoomFactor, zoomFactor);
}

void Camera::mousePressEvent(QMouseEvent *event){
    //calculate scene coordinates of the cursor and find items intersecting that position
    QList<QGraphicsItem *> selectedItemsQ = this->scene()->items(mapToScene(event->pos()), Qt::IntersectsItemBoundingRect);

    //convert to std list to be able to properly use auto loops
    std::list<QGraphicsItem *> selectedItems = std::list<QGraphicsItem *>(selectedItemsQ.begin(), selectedItemsQ.end());
    if(event->button() == Qt::MouseButton::LeftButton){
       if(placer != nullptr){
           placer->placeVesselObject();
           delete placer;
           placer = nullptr;
       }
       else{
       for(auto item : selectedItems){
           //Check if point intersects with one of interaction buttons. Those are the first priority
           for(auto interaction : activeInterractions){
               if(item->type() == 171){
                   interaction->Interract();

                   return;
               }
           }



           //if it is not a GUI element, it is an VesselObject
           for (auto object : selectedItems) {
               if(object->type() == OBJECT_TYPE){
                    VesselObject * selected = static_cast<VesselObject *>(object);

                   followingVessel =  selected->getVessel();

                   //remove previous selector
                   if(selector != nullptr){
                       this->scene()->removeItem(selector);
                       delete selector;
                   }
                   selector = new SelectedVesselObjectSprite("/home/vitang/Dev/Memoriam_Telluris/assets/selectorexample.png", selected);

                   this->scene()->addItem(selector);

                   return;
               }
           }
       }
       }
    }
    else if(event->button() == Qt::MouseButton::RightButton){
        for(auto graphicsitem : selectedItems){

            if(graphicsitem->type() == OBJECT_TYPE){
                 VesselObject * selectedObj = static_cast<VesselObject *>(graphicsitem);

                 this->scene()->removeItem(graphicsitem);


                 selectedObj->getVessel()->removeVesselObject(selectedObj);

                 if(selectedObj == this->followingItem){
                    this->scene()->removeItem(selector);
                    delete selector;
                    selector = nullptr;
                    followingItem = nullptr;
                 }

                 delete  selectedObj;

                 return;
            }
        }
    }
}

void Camera::mouseDoubleClickEvent(QMouseEvent * event){
    //calculate scene coordinates of the cursor and find items intersecting that position
    QList<QGraphicsItem *> selectedItemsQ = this->scene()->items(mapToScene(event->pos()));

    //convert to std list to be able to properly use auto loops
    std::list<QGraphicsItem *> selectedItems = std::list<QGraphicsItem *>(selectedItemsQ.begin(), selectedItemsQ.end());

    if(selectedItems.size() == 0){
        coords = mapToScene(event->pos());
        return;
    }
    else{
        for(auto item : selectedItems){
           if(item->type() == OBJECT_TYPE){
                this->centerOn(item);
                this->followingItem = item;
                return;
            }
        }
    }
}

void Camera::updateCameraPosition(){
    if(followingItem != nullptr){
        this->centerOn(followingItem);
        if(followingItem->rotation() != angle){
            this->rotate(angle - followingItem->rotation());
            angle = followingItem->rotation();
         /*   if(followingItem->type() == OBJECT_TYPE){
                VesselObject * followingVesselObject = static_cast<VesselObject *>(followingItem);
                angle -= followingVesselObject->getOwnRotation();
            }*/

        }
        coords = followingItem->pos();
    }
    else{
        this->centerOn(coords);
    }
}

float Camera::getAngle(){
    return angle;
}

void Camera::setPlacer(VesselObjectPlacementSprite *newplacer){
    placer = newplacer;
}


Vessel * Camera::getVessel(){
    return followingVessel;
}

void Camera::setSettings(GameSettings *newSettings){
    settings = newSettings;
}
