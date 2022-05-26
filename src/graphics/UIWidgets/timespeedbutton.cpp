#include "timespeedbutton.h"
#include <QIcon>
#include <src/game.h>

TimeSpeedSetter::TimeSpeedSetter(float timespeed, Game * toConnect){
    this->timeSpeed = timespeed;
    this->game = toConnect;
}

void TimeSpeedSetter::setTime(){
    game->setNewTimeStep(timeSpeed);
}

TimeSpeedSetter::~TimeSpeedSetter(){

}

TimeSpeedButton::TimeSpeedButton(QString spritefile, float x, float y, float width, float height, float timeStep, Game * game)
{
    this->setGeometry(x,y,width, height);

    this->setIcon(QIcon(spritefile));
    this->connectedSetter = new TimeSpeedSetter(timeStep, game);
    this->setStyleSheet("background-color: rgba(100, 100, 100, 0); border-color: rgba(100, 100, 100, 0);");

    QObject::connect(this, &QPushButton::pressed, this->connectedSetter, &TimeSpeedSetter::setTime);
}

TimeSpeedButton::~TimeSpeedButton(){
    delete connectedSetter;
}
