#include "interfacesubwindow.h"
#include <QKeyEvent>


InterfaceSubwindow::InterfaceSubwindow(QWidget * parentWidget,  QRect & windowRect, QObject * toConnect, QString stylesheet)
{
    this->setParent(parentWidget);
    this->setGeometry(windowRect);
    connectedObject = toConnect;
    this->setStyleSheet(stylesheet);

}

void InterfaceSubwindow::keyPressEvent(QKeyEvent * event){


    lastKeyPressed = event->key();
}

int InterfaceSubwindow::getLastPressedKey(){
    return lastKeyPressed;
}

void InterfaceSubwindow::addSideWidget(QWidget * widget,  QRect & pos, QWidget * optionalParent){
    if(optionalParent != nullptr){
        widget->setParent(optionalParent);
    }
    else{
        widget->setParent(this);
    }
    widget->setGeometry(pos);
}
