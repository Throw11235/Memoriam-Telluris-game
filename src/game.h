#ifndef GAME_H
#define GAME_H
#include <list>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <src/graphics/camera.h>
#include  <src/nbodysim/nbody2d.h>
#include <src/atmospherics/gascontainer.h>
#include <src/object/vesselobject.h>
#include <src/object/interraction/interaction.h>
#include <src/gamesettings.h>
#include <src/uimanager.h>
#include <src/nbodysim/nbodyphysicssimulation.h>

class Game : public QObject
{
    //Lists of singleton objects
    std::list<Gas*> gases;
    std::list<Interaction*> interactions;


    float timeStep = 0.0;

    QWidget * windowCentralWidget = nullptr;



    std::map<std::string ,VesselObjectType*> objectTypes = {};

    //Lists of object with corresponding functions responsible for updating them
    std::list<NBody*> nBodies  = {};

    void updateNBodySim();

    std::list<Vessel*> vesselsOnMap = {};

    void UpdateVessels();

    std::list<VesselObject*> objectsOnMap = {};

    void UpdateVesselObjects();

    std::list<GasContainer*> activeGasContainers = {};

    void UpdateAtmospherics();

    QGraphicsScene * displayedMapScene;


    std::list<QWidget *> backgroundUI = {};

    std::list<QWidget *> foregroundUI = {};

    Camera * camera = nullptr;

    GameSettings * settings = nullptr;


    UImanager * interfaceManager = nullptr;


    QTimer Timer;
public:


    QGraphicsView * getCamera();
    QGraphicsScene * getScene();

    void setNewCamera(Camera * newCamera);
    void setNewScene(QGraphicsScene & newScene);

     std::list<QWidget *> & getForegroundWidgets();

     std::list<QWidget *> & getBackgroundWidgets();

    void populateGame();

    void startEditor();

    void setWindowWidget(QWidget * toConnect);

    void setNewTimeStep(float newTimeStep);

    Game(QWidget * centralWidget, UImanager * interfacemanager, GameSettings * connectedsettings);

};

#endif // GAME_H
