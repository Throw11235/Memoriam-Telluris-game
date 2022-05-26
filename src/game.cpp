#include "game.h"
#include <QThread>

#include <src/graphics/UIWidgets/decorativeuiwidget.h>
#include <src/graphics/UIWidgets/timespeedbutton.h>
#include <src/graphics/objectplacementsprite.h>
#include <src/graphics/UIWidgets/objectplacementfactorybutton.h>

#include <src/graphics/masscenterindicator.h>
#include <QtOpenGL/QtOpenGL>

#include <fstream>
#include <iostream>

Game::Game(QWidget * centralWidget, UImanager * interfacemanager, GameSettings * connectedsettings)
{
    windowCentralWidget = centralWidget;
    interfaceManager = interfacemanager;

    displayedMapScene = new QGraphicsScene(-40000,-40000,80000,80000);
    displayedMapScene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    camera = new Camera(interfaceManager);
    camera->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    camera->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    camera->setScene(displayedMapScene);

    camera->setRenderHint(QPainter::Antialiasing);
    camera->setBackgroundBrush(QBrush(QColor(80, 80,80)));

    camera->setCacheMode(QGraphicsView::CacheBackground);
    camera->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


    camera->resize(1920, 1080);



    QOpenGLWidget *gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(4);
    gl->setFormat(format);

    camera->setViewport(gl);



    camera->setScene(displayedMapScene);

    //Setting up time controls in upper right corner
    QScrollArea * timingField = new QScrollArea();
    timingField->setGeometry(1380, -15, 700, 125);

    TimeSpeedButton * pause = new TimeSpeedButton("/home/vitang/Dev/Memoriam_Telluris/assets/pauseicon.png",20,25,30,30,0,this);
    pause->setParent(timingField);
    TimeSpeedButton * normalSpeed = new TimeSpeedButton("/home/vitang/Dev/Memoriam_Telluris/assets/normalspeed.png",70,25,30,30,0.5,this);
    normalSpeed->setParent(timingField);
    TimeSpeedButton * tripleSpeed = new TimeSpeedButton("/home/vitang/Dev/Memoriam_Telluris/assets/triplespeed.png",120,25,30,30,1.5,this);
    tripleSpeed->setParent(timingField);

    QSlider * timeDial = new QSlider(Qt::Orientation::Horizontal, timingField);
    timeDial->setGeometry(10, 80, 520, 10);

    foregroundUI.push_back(timingField);


    QScrollArea * ordersField = new QScrollArea();
    ordersField->setGeometry(-20, 750, 650, 350);

    QScrollArea * constSubField = new QScrollArea(ordersField);
    constSubField->setStyleSheet("background-color: grey; border: 2px solid black; border-radius: 0px;");
    constSubField->setGeometry(20, 50, 630, 300);

    VesselObjectPlacementFactoryButton * floorB = new VesselObjectPlacementFactoryButton("/home/vitang/Dev/Memoriam_Telluris/assets/1meterfloorexample.png", 10, 10, 64, 64, 100, camera);
    floorB->setParent(constSubField);
    VesselObjectPlacementFactoryButton * wallB = new VesselObjectPlacementFactoryButton("/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png", 70, 10, 16, 16, 20, camera);
    wallB->setParent(constSubField);
    VesselObjectPlacementFactoryButton * hazardB = new VesselObjectPlacementFactoryButton("/home/vitang/Dev/Memoriam_Telluris/assets/smallfloorexample.png", 130, 10, 16, 16, 20, camera);
    hazardB->setParent(constSubField);

    foregroundUI.push_back(ordersField);


    QScrollArea * characterField = new QScrollArea();
    characterField->setGeometry(1350, 810, 600, 300);

    QTextEdit * nameplate = new QTextEdit("No character selected");
    nameplate->setGeometry(10, 10, 140 , 30);
    nameplate->setStyleSheet("background-color: grey; border: 2px solid black; border-radius: 10px;");
    nameplate->setParent(characterField);

    QLabel * characterButton = new QLabel();
    characterButton->setPixmap(QPixmap("/home/vitang/Dev/Memoriam_Telluris/assets/emptycharui.png"));
    characterButton->setGeometry(10,50, 140, 140);
    characterButton->setStyleSheet("background-color: grey; border: 2px solid black; border-radius: 20px;");

    characterButton->setParent(characterField);

    QScrollArea * attributesField = new QScrollArea(characterField);
    attributesField->setGeometry(160 ,10, 400, 200);
    attributesField->setStyleSheet("background-color: grey; border: 2px solid black; border-radius: 20px;");

    foregroundUI.push_back(characterField);




    settings = connectedsettings;

    camera->setSettings(settings);

}


QGraphicsView * Game::getCamera(){
    return camera;
}

QGraphicsScene * Game::getScene(){
    return displayedMapScene;
}

void Game::setNewCamera(Camera *newCamera){
    camera = newCamera;
}

void Game::setWindowWidget(QWidget *toConnect){
    windowCentralWidget = toConnect;

}



void Game::UpdateVesselObjects(){
    for(auto obj : objectsOnMap){
        obj->UpdateObject();
    }
}

void Game::UpdateVessels(){
    for(auto vessel : vesselsOnMap){
        vessel->move(timeStep);
    }
}

void Game::updateNBodySim(){
    for(auto nbody : nBodies){
        nbody->advance(1);
    }
}

void Game::UpdateAtmospherics(){
    for(auto containter : activeGasContainers){
        containter->processContainer();
    }
}



void Game::populateGame(){





    Vessel * basevessel = new Vessel(0,0,0,90, displayedMapScene);

    vesselsOnMap.push_back(basevessel);

    /*
    std::list<VesselObject *> vesselparts = {};
    for(int i = -64; i <= 64; i+= 64){
        for(int j = -64; j  <= 64; j += 64){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/1meterfloorexample.png";
            VesselObject * tile = new VesselObject(spritename, {}, 64, 64, basevessel, i,j, 100);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
    }

    for(int i = 144; i <= 208; i+= 64){
        for(int j = -64; j  <= 64; j += 64){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/1meterfloorexample.png";
            VesselObject * tile = new VesselObject(spritename, {}, 64, 64, basevessel, i,j, 100);
            vesselparts.push_back(tile);
         //   tile->rotateClockwise(90);
            displayedMapScene.addItem(tile);
        }
    }

    for(int i = -144; i >= -208; i-= 64){
        for(int j = -64; j  <= 64; j += 64){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/1meterfloorexample.png";
            VesselObject * tile = new VesselObject(spritename, {}, 64, 64, basevessel, i,j, 100);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);
        }
    }

    for(int i = -88; i <= 88; i += 16){
        if(i < -40 || i > 40){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, 104,i, 20);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);
        }
        else{
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/smallfloorexample.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, 104,i, 20);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
    }
    for(int i = -88; i <= 88; i += 16){
        QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
        VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, -104,i, 20);
        vesselparts.push_back(tile);
        displayedMapScene.addItem(tile);
    }
    for(int i = -88; i <= 88; i += 16){
        QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
        VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, -248,i, 20);
        vesselparts.push_back(tile);
        displayedMapScene.addItem(tile);
    }
    for(int i = -88; i <= 88; i += 16){
        if(i < -40 || i > 40){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, 248,i, 20);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);
        }
        else{
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/smallfloorexample.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, 248,i, 20);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);
        }
    }


    for(int i = -232; i <= 232; i += 16){
        if((i - 104) % 208 != 0){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, i,104, 20);
            tile->rotateClockwise(90);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
        else{
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexampletriple.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, i,104, 20);
            tile->rotateClockwise(270);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
    }

    for(int i = -232; i <= 232; i += 16){
        if((i - 104) % 208 != 0){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplestraight.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, i,-104, 20);
            tile->rotateClockwise(90);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
        else{
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexampletriple.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, i,-104, 20);
            tile->rotateClockwise(90);
            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);

        }
    }


    for(int i = 0; i <2 ; i++){
        for(int j = 0; j < 2; j++){
            QString spritename = "/home/vitang/Dev/Memoriam_Telluris/assets/wallexamplecorner.png";
            VesselObject * tile = new VesselObject(spritename, {}, 16, 16, basevessel, -248 + i * 496, - 104 + j * 208, 20);
            switch(i + 2 * j){
                case 0:
                    tile->rotateClockwise(0);
                break;
                case 1:
                    tile->rotateClockwise(90);
                break;
                case 2:
                   tile->rotateClockwise(270);
                break;
                case 3:
                    tile->rotateClockwise(180);
                break;
            }

            vesselparts.push_back(tile);
            displayedMapScene.addItem(tile);
        }
    }


    basevessel->addVesselObjectList(vesselparts);
    */


    std::ifstream freader("/home/vitang/Dev/jsontest.json");
    nlohmann::json jsfile = nlohmann::json::parse(freader);

    std::list<std::string> exeptions = {};
    basevessel->loadFromJson(jsfile, displayedMapScene, objectTypes, exeptions);
    freader.close();

    for(const auto & exmessage : exeptions){
        std::cout << exmessage << std::endl;
    }


    /*
    camera->setScene(displayedMapScene);

    camera->setRenderHint(QPainter::Antialiasing);
    camera->setBackgroundBrush(QBrush(QColor(80, 80,80)));

    camera->setCacheMode(QGraphicsView::CacheBackground);
    camera->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


    camera->resize(1920, 1080);
    */


    QObject::connect(&Timer, &QTimer::timeout, displayedMapScene, &QGraphicsScene::advance);
    Timer.start(1000 / 33);

    basevessel->setRotation(90);
    basevessel->setSpeed(QVector2D(2, 1));
    basevessel->setRotationSpeed(-1);

    MassCenterIndicator * masspointer = new MassCenterIndicator(basevessel);

    displayedMapScene->addItem(masspointer);


    // std::ofstream fwriter("/home/vitang/Dev/jsontest.json");
    // fwriter << basevessel->loadToJson();
    // fwriter.close();


    /*
    settings->setKeybind("ForwardKey", Qt::Key_W);
    settings->setKeybind("BackKey", Qt::Key_S);
    settings->setKeybind("LeftKey", Qt::Key_A);
    settings->setKeybind("RightKey", Qt::Key_D);

    settings->setKeybind("RotRightKey", Qt::Key_E);
    settings->setKeybind("RotLeftKey", Qt::Key_Q);

    settings->setKeybind("TempSaveKey", Qt::Key_Slash);
    settings->setKeybind("SystemMapKey", Qt::Key_M);

    */

    this->timeStep = 0.5;
    Timer.connect(&Timer, &QTimer::timeout,this, &Game::UpdateVessels);

    QObject::connect(&Timer, &QTimer::timeout, camera, &Camera::updateCameraPosition);

    /*
    CelestialBody * Sol = new CelestialBody(nullptr, QVector2D(0,0), QVector2D(0,0));
    CelestialBody * Earth = new CelestialBody(Sol, QVector2D(0,0), QVector2D(0,0));
    CelestialBody * Luna = new CelestialBody(Earth, QVector2D(0,0), QVector2D(0,0));

    std::list<NBody *> simbodies = {};

    NBodyPhysicsSimulation * nbsim = new NBodyPhysicsSimulation(Sol ,simbodies);

    nbsim->addCelestial(Sol);
    nbsim->addCelestial(Earth);
    nbsim->addCelestial(Luna);

    nbsim->setTimeStep(20);

    nbsim->getSystemView()->resize(1920,1080);
    nbsim->getSystemView()->setParent(windowCentralWidget);

    QObject::connect(&Timer, &QTimer::timeout, nbsim, &NBodyPhysicsSimulation::advanceSimulation);
    */

    Timer.start(1);

   // QThread * vesselThread = new QThread();

   // Timer.moveToThread(vesselThread);
   // vesselThread->start();

    VesselObjectPlacementSprite * placer = new VesselObjectPlacementSprite(camera, new VesselObject("/home/vitang/Dev/Memoriam_Telluris/assets/1meterfloorexample.png", {}, 64, 64, nullptr, 0,0, 100) ,basevessel);

    camera->setPlacer(placer);

    displayedMapScene->addItem(placer);

   // basevessel->deployGrid();
}

std::list<QWidget *> & Game::getBackgroundWidgets(){
    return backgroundUI;
}

std::list<QWidget *> & Game::getForegroundWidgets(){
    return foregroundUI;
}

void Game::setNewTimeStep(float newTimeStep){
    timeStep = newTimeStep;
}

void Game::startEditor(){

    for(QObject * menuWidget : windowCentralWidget->children()){
        delete menuWidget;
    }


    //populateGame();

    this->getCamera()->setParent(windowCentralWidget);

    for(auto widget : this->getBackgroundWidgets()){
        widget->setParent(windowCentralWidget);
        std::cout << "wid " << widget->parentWidget()->geometry().width() << std::endl;
    }

    for(auto widget : this->getForegroundWidgets()){
        widget->setParent(windowCentralWidget);
        std::cout << "wid " << widget->parentWidget()->geometry().width()  << std::endl;
    }

}

