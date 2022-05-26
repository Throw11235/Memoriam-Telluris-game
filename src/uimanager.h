#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <QWidget>
#include <QMainWindow>

class GameSettings;

class UImanager : public QObject
{
    std::list<QWidget*> activeInterfaceList = {};
    std::list<QWidget*> foregroundWidgetList = {};
    std::list<QWidget*> backgroundWidgetList = {};

    QWidget * centralWidget = nullptr;
    QMainWindow * gameWindow = nullptr;

    GameSettings * connectedSettings = nullptr;


public:
    UImanager(QWidget * windowcentralwidget, QMainWindow * window);

    void setCentralWidget(QWidget * windowcentralwidget);

    void clearScreen();
    void clearActiveInterface();

    std::list<QWidget*> & getForegroundWidgets();
    std::list<QWidget*> & getBackgroundWidgets();
    std::list<QWidget*> & getInterfaceWidgets();

    void drawEditorLayout();
    void drawMainMenuLayout();
    void drawGameLayout();

    void showInterface(QObject * interfaceObject);


    void showMenu();

    void showSettingsUI();

    void closeGame();

};

#endif // UIMANAGER_H
