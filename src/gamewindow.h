#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <src/game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT


public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Game * gameSingleton;

    Ui::GameWindow *ui;
};
#endif // GAMEWINDOW_H
