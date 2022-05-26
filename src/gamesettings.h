#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <nlohmann/json.hpp>
#include <QWindow>
#include <QSlider>
#include <src/uimanager.h>
#include <src/graphics/interfacesubwindow.h>


class KeyBind{

    QString keyName = "";
    QString bindName = "";

    int keyInt = 0;

public:

    KeyBind(int key, QString binding);

    QString getKeyName();
    QString getBindingName();

    void ChangeBinding();

};



class GameSettings : public QObject
{
    std::map<std::string, int> keybindings = {};
    std::string selectedKeybind = "";

    std::map<std::string, float> sensitivityParams = {};

    QWidget * settingsarea = nullptr;
    InterfaceSubwindow * settingsWindow = nullptr;

    QSlider * masterVolumeSlider = nullptr;
    double masterVolume = 0.0;

    QSlider * musicVolumeSlider = nullptr;
    double musicVolume = 0.0;

    QSlider * gameVolumeSlider = nullptr;
    double gameVolume = 0.0;

    QSlider * notificationVolumeSlider = nullptr;
    double notificationVolume = 0.0;



    QRectF resolution = QRectF(0,0,1920,1080);

    double brightness = 0.0;

public:

    GameSettings();

    void setKeybind(std::string key, int binding);

    void setSettingsSubwindow(InterfaceSubwindow * toSet);

    nlohmann::json loadToJson();
    void loadFromJson(nlohmann::json & configjson);

    std::map<std::string,  int> & getKeybinds();

    void setupKeybindsUI();

    void setupAudioUI();

    void setupGameplayUI();

    void setupGraphicsUI();

    double getMasterVolume();
    void setMasterVolume();

    double getMusicVolume();
    void setMusicVolume();

    double getGameVolume();
    void setGameVolume();

    double getNotifyVolume();
    void setNotifyVolume();




};

#endif // GAMESETTINGS_H
