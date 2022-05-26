#ifndef MAINMENU_H
#define MAINMENU_H
#include <src/game.h>
#include <QMainWindow>
#include <QHBoxLayout>

class MainMenu
{
    QLayout * windowLayout = nullptr;

public:
    MainMenu(QLayout * toConnect);

    void startGame();

    void showMods();
    void showConfig();


};

#endif // MAINMENU_H
