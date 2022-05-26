#include "gamesettings.h"
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QKeySequence>

void clearLayout(QLayout * layout){
    while (QLayoutItem* leftoveritem = layout->takeAt(0))
    {

        if (QWidget* widget = leftoveritem->widget()){
                delete widget;
        }

        if (QLayout* childLayout = leftoveritem->layout()){
            clearLayout(childLayout);
        }

        delete leftoveritem;
    }
}



GameSettings::GameSettings()
{



    this->setKeybind("ForwardKey", Qt::Key_W);
    this->setKeybind("BackKey", Qt::Key_S);
    this->setKeybind("LeftKey", Qt::Key_A);
    this->setKeybind("RightKey", Qt::Key_D);

    this->setKeybind("RotRightKey", Qt::Key_E);
    this->setKeybind("RotLeftKey", Qt::Key_Q);

    this->setKeybind("TempSaveKey", Qt::Key_Slash);
    this->setKeybind("SystemMapKey", Qt::Key_M);


}

void GameSettings::setKeybind(std::string key, int binding){
    if(keybindings.find(key) == keybindings.end()){
        keybindings.insert({key, binding});
    }
    else{
        keybindings[key] = binding;
    }


}


void GameSettings::loadFromJson(nlohmann::json & configjson){
    for(const auto & keybindingjson : configjson["Keybindings"]){
        nlohmann::json keybindinginstance = keybindingjson;
        setKeybind(keybindinginstance["Binding"] ,keybindinginstance["Key"]);
    }
}

nlohmann::json  GameSettings::loadToJson(){
    nlohmann::json  configjson;

    std::list<nlohmann::json> keybindsjson = {};
    for(const auto & keybindtojson : keybindings){
        nlohmann::json  keybindinstance;
        keybindinstance["Key"] = keybindtojson.first;
        keybindinstance["Binding"] = keybindtojson.second;
        keybindsjson.push_back(keybindinstance);
    }
    configjson["Keybindings"] = keybindsjson;


    return configjson;
}

std::map<std::string,  int> & GameSettings::getKeybinds(){
    return keybindings;
}



void GameSettings::setupKeybindsUI(){
    delete settingsarea;

    QWidget * settingsFrame = new QWidget(settingsWindow);

    settingsFrame->setGeometry(10,150,1700, 700);

    settingsFrame->setLayout(new QVBoxLayout());

    settingsFrame->show();

    settingsarea = settingsFrame;

    for(const auto & keybind : keybindings){
        QScrollArea * line = new QScrollArea();
        line->setLayout(new QHBoxLayout);

        QLabel * Bindname = new QLabel(QString::fromStdString(keybind.first));
        line->layout()->addWidget(Bindname);

        QLabel * Keyname = new QLabel(QKeySequence(keybind.second).toString());
        line->layout()->addWidget(Keyname);

        QPushButton * changeButton = new QPushButton("Change binding");
        line->layout()->addWidget(changeButton);

        settingsFrame->layout()->addWidget(line);

 /*     line->show();
        Bindname->show();
        Keyname->show();
        changeButton->show();
        */
    }

}

void GameSettings::setupAudioUI(){
    delete settingsarea;

    QWidget * settingsFrame = new QWidget(settingsWindow);

    settingsFrame->setGeometry(10,150,1700, 700);

    settingsFrame->setLayout(new QVBoxLayout());

    settingsFrame->show();

    settingsarea = settingsFrame;


    QScrollArea * masterLine = new QScrollArea();
    masterLine->setLayout(new QHBoxLayout);

    QLabel * masName = new QLabel("Master Volume");
    masterLine->layout()->addWidget(masName);

    QSlider * masSlider = new QSlider(Qt::Orientation::Horizontal);
    masterVolumeSlider = masSlider;
    QObject::connect(masSlider, &QSlider::sliderReleased, this, &GameSettings::setMasterVolume);
    masterLine->layout()->addWidget(masSlider);

    settingsFrame->layout()->addWidget(masterLine);


    QScrollArea * musicLine = new QScrollArea();
    musicLine->setLayout(new QHBoxLayout);

    QLabel * bgmName = new QLabel("Music Volume");
    musicLine->layout()->addWidget(bgmName);

    QSlider * bgmSlider = new QSlider(Qt::Orientation::Horizontal);
    musicVolumeSlider = bgmSlider;
    QObject::connect(bgmSlider, &QSlider::sliderReleased, this, &GameSettings::setMusicVolume);
    musicLine->layout()->addWidget(bgmSlider);

    settingsFrame->layout()->addWidget(musicLine);


    QScrollArea * notifyLine = new QScrollArea();
    notifyLine->setLayout(new QHBoxLayout);

    QLabel * notName = new QLabel("Notification Volume");
    notifyLine->layout()->addWidget(notName);

    QSlider * notSlider = new QSlider(Qt::Orientation::Horizontal);
    notificationVolumeSlider = notSlider;
    QObject::connect(notSlider, &QSlider::sliderReleased, this, &GameSettings::setNotifyVolume);
    notifyLine->layout()->addWidget(notSlider);

    settingsFrame->layout()->addWidget(notifyLine);


    QScrollArea * gameLine = new QScrollArea();
    gameLine->setLayout(new QHBoxLayout);

    QLabel * gmpName = new QLabel("Game Volume");
    gameLine->layout()->addWidget(gmpName);

    QSlider * gmpSlider = new QSlider(Qt::Orientation::Horizontal);
    gameVolumeSlider = gmpSlider;
    QObject::connect(gmpSlider, &QSlider::sliderReleased, this, &GameSettings::setGameVolume);
    gameLine->layout()->addWidget(gmpSlider);

    settingsFrame->layout()->addWidget(gameLine);
}

void GameSettings::setupGameplayUI(){
    delete settingsarea;

    QWidget * settingsFrame = new QWidget(settingsWindow);

    settingsFrame->setGeometry(10,150,1700, 700);

    settingsFrame->setLayout(new QVBoxLayout());

    settingsFrame->show();

    settingsarea = settingsFrame;
}

void GameSettings::setupGraphicsUI(){
    delete settingsarea;

    QWidget * settingsFrame = new QWidget(settingsWindow);

    settingsFrame->setGeometry(10,150,1700, 700);

    settingsFrame->show();

    settingsarea = settingsFrame;

}


void GameSettings::setSettingsSubwindow(InterfaceSubwindow *toSet){
    settingsWindow = toSet;
}


double GameSettings::getMasterVolume(){
    return masterVolume;
}

void GameSettings::setMasterVolume(){
    masterVolume = masterVolumeSlider->value();
}

double GameSettings::getGameVolume(){
    return gameVolume;
}

void GameSettings::setGameVolume(){
    gameVolume = gameVolumeSlider->value();
}

double GameSettings::getMusicVolume(){
    return musicVolume;
}

void GameSettings::setMusicVolume(){
    musicVolume = musicVolumeSlider->value();
}

double GameSettings::getNotifyVolume(){
    return notificationVolume;
}

void GameSettings::setNotifyVolume(){
    notificationVolume = notificationVolumeSlider->value();
}
