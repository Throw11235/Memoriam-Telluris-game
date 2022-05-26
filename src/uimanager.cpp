#include "uimanager.h"
#include <src/game.h>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <src/gamesettings.h>
#include <src/graphics/interfacesubwindow.h>

#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeySequence>



UImanager::UImanager(QWidget * windowcentralwidget, QMainWindow * window)
{
    gameWindow = window;
    centralWidget = windowcentralwidget;

    connectedSettings = new GameSettings();
}

void UImanager::setCentralWidget(QWidget * windowcentralwidget){
    centralWidget = windowcentralwidget;
}


void UImanager::drawMainMenuLayout(){
    if(centralWidget != nullptr){
        clearScreen();

        QLabel * mainMenuImg = new QLabel(centralWidget);
        mainMenuImg->resize(1920,1080);
        mainMenuImg->setPixmap(QPixmap("/home/vitang/Dev/Memoriam_Telluris/assets/mainmenu.jpg"));

        QPushButton * startButton = new QPushButton(centralWidget);
        startButton->setGeometry(1600, 280, 150, 50);
        startButton->setText("Start Game");


        QPushButton * loadButton = new QPushButton(centralWidget);
        loadButton->setGeometry(1600, 340, 150, 50);
        loadButton->setText("Load Game");


        QPushButton * editorButton = new QPushButton(centralWidget);
        editorButton->setGeometry(1600, 400, 150, 50);
        editorButton->setText("Vessel editor");
        QObject::connect(editorButton, &QPushButton::pressed, this, &UImanager::drawEditorLayout);

        QPushButton * settingsButton = new QPushButton(centralWidget);
        settingsButton->setGeometry(1600, 460, 150, 50);
        settingsButton->setText("Settings");
        QObject::connect(settingsButton, &QPushButton::pressed, this, &UImanager::showSettingsUI);

        QPushButton * modButton = new QPushButton(centralWidget);
        modButton->setGeometry(1600, 520, 150, 50);
        modButton->setText("Mods");


        QPushButton * exitButton = new QPushButton(centralWidget);
        exitButton->setGeometry(1600, 600, 150, 50);
        exitButton->setText("Exit");
        QObject::connect(exitButton, &QPushButton::pressed, this, &UImanager::closeGame);
    }
}


void UImanager::drawEditorLayout(){
    if(centralWidget != nullptr){
        clearScreen();



        Game * gameInstance = new Game(centralWidget, this, connectedSettings);

        //gameInstance->setWindowWidget(centralWidget);

        gameInstance->populateGame();

        gameInstance->getCamera()->setParent(centralWidget);

        gameInstance->getCamera()->show();

        for(auto widget : gameInstance->getBackgroundWidgets()){
            widget->setParent(centralWidget);
            widget->show();

        }

        for(auto widget : gameInstance->getForegroundWidgets()){
            widget->setParent(centralWidget);
            widget->show();


        }

    }
}

void UImanager::drawGameLayout(){
    if(centralWidget != nullptr){
        clearScreen();

    }
}


void UImanager::showMenu(){
    clearActiveInterface();


    QScrollArea * menuBar = new QScrollArea(centralWidget);
    menuBar->setGeometry(750, 200 , 420 ,680);
    menuBar->setStyleSheet("background-color: grey; border: 2px solid Grayrgb(47,0,71); border-radius: 20px;");
    menuBar->show();
    getInterfaceWidgets().push_back(menuBar);


    QPushButton * resumeButton = new QPushButton("Resume", menuBar);
    resumeButton->setGeometry(10,10, 400, 100);
    QObject::connect(resumeButton, &QPushButton::clicked, this, &UImanager::clearActiveInterface);
    resumeButton->setStyleSheet("QPushButton:hover { background-color: cyan}");
    resumeButton->show();

    QPushButton * saveButton = new QPushButton("Save spacecraft", menuBar);
    saveButton->setGeometry(10,120, 400, 100);

    saveButton->setStyleSheet("QPushButton:hover { background-color: cyan}");

    saveButton->show();

    QPushButton * loadButton = new QPushButton("Load Spacecraft", menuBar);
    loadButton->setGeometry(10,230, 400, 100);

    loadButton->setStyleSheet("QPushButton:hover { background-color: cyan}");

    loadButton->show();

    QPushButton * settingsButton = new QPushButton("Settings", menuBar);
    settingsButton->setGeometry(10,340, 400, 100);
    QObject::connect(settingsButton, &QPushButton::clicked, this, &UImanager::showSettingsUI);

    settingsButton->setStyleSheet("QPushButton:hover { background-color: cyan}");

    settingsButton->show();

    QPushButton * exitButton = new QPushButton("Exit", menuBar);
    exitButton->setGeometry(10, 560 , 400, 100);
    QObject::connect(exitButton, &QPushButton::clicked, this, &UImanager::closeGame);

    exitButton->setStyleSheet("QPushButton:hover { background-color: cyan}");

    exitButton->show();

}


void UImanager::clearActiveInterface(){
    for(auto widget : activeInterfaceList){
        delete widget;
    }
    activeInterfaceList = {};
}

void UImanager::clearScreen(){
    for(auto widget : centralWidget->children()){
        delete widget;
    }
}


std::list<QWidget*> & UImanager::getBackgroundWidgets(){
    return backgroundWidgetList;
}

std::list<QWidget*> & UImanager::getForegroundWidgets(){
    return foregroundWidgetList;
}

std::list<QWidget*> & UImanager::getInterfaceWidgets(){
    return activeInterfaceList;
}


void UImanager::closeGame(){
    gameWindow->close();
}

void UImanager::showSettingsUI(){

    // main body

    QRect rect = QRect(100, 100 , 1720 ,880);
    InterfaceSubwindow * settingsWindow = new InterfaceSubwindow(centralWidget, rect, nullptr);
    //settingsWindow->setGeometry(100, 100 , 1720 ,880);
    settingsWindow->show();
    this->getInterfaceWidgets().push_back(settingsWindow);

    connectedSettings->setSettingsSubwindow(settingsWindow);

    //upper part with categories
    QWidget * categoryframe = new QWidget(settingsWindow);
    categoryframe->setLayout(new QHBoxLayout);
    categoryframe->setGeometry(10,10,1700, 120);
    categoryframe->show();

    QPushButton * keysButton = new QPushButton("Keybinds");
    categoryframe->layout()->addWidget(keysButton);
    QObject::connect(keysButton, &QPushButton::clicked, connectedSettings, &GameSettings::setupKeybindsUI);
    keysButton->show();

    QPushButton * graphButton = new QPushButton("Graphics");
    categoryframe->layout()->addWidget(graphButton);
    QObject::connect(keysButton, &QPushButton::clicked, connectedSettings, &GameSettings::setupGraphicsUI);
    graphButton->show();

    QPushButton * soundButton = new QPushButton("Audio");
    categoryframe->layout()->addWidget(soundButton);
    QObject::connect(keysButton, &QPushButton::clicked, connectedSettings, &GameSettings::setupAudioUI);
    soundButton->show();

    QPushButton * gameButton = new QPushButton("Gameplay");
    categoryframe->layout()->addWidget(gameButton);
    QObject::connect(keysButton, &QPushButton::clicked, connectedSettings, &GameSettings::setupGameplayUI);

    gameButton->show();


    /*
    //lower part with most of the info
    QScrollArea * settingsframe = new QScrollArea(settingsWindow);
    settingsframe->setLayout(new QVBoxLayout);
    settingsframe->setGeometry(10,150,1700, 700);
    settingsframe->addScrollBarWidget(new QScrollBar,Qt::AlignRight);
    settingsframe->show();

    connectedSettings->setSettingsFrameWidget(settingsframe);
    */


    connectedSettings->setupKeybindsUI();

}
