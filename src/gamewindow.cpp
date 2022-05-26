#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QStackedLayout>
#include <QMdiArea>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPushButton>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    //gameSingleton = new Game;
    //gameSingleton->populateGame();
    ui->setupUi(this);



    QWidget * cWidget = new QWidget();

    this->setCentralWidget(cWidget);

    cWidget->setStyleSheet("background-color: grey; border: 0px solid Grayrgb(47,0,71); border-radius: 20px;");

    cWidget->resize(1980, 1080);
    cWidget->move(-10,-10);

    UImanager * interfaceManager = new UImanager(cWidget, this);

    interfaceManager->drawMainMenuLayout();


}

GameWindow::~GameWindow()
{
    delete ui;
}

