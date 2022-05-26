#ifndef TIMESPEEDBUTTON_H
#define TIMESPEEDBUTTON_H
#include <QPushButton>

class Game;


class TimeSpeedSetter : public QObject
{
    Game * game = nullptr;

    float timeSpeed = 0.0;
public:
    TimeSpeedSetter(float timespeed, Game * toConnect);
    ~TimeSpeedSetter();

    void setTime();
};



class TimeSpeedButton : public QPushButton
{
    QString pathToSpriteFile = "";

    TimeSpeedSetter * connectedSetter = nullptr;
public:
    TimeSpeedButton(QString spritefile, float x, float y, float width, float height, float timeStep, Game * game);
    ~TimeSpeedButton();

};

#endif // TIMESPEEDBUTTON_H
