#include "modloader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <QFileSystemWatcher>


Modloader::Modloader(Game * toConnect)
{
    gameInstance = toConnect;
}

void Modloader::loadMods(){

}

void Modloader::loadIndividualMod(std::string pathToFile){
    if(gameInstance != nullptr){
        std::ifstream filereader;
        filereader.open(":/mods/" + pathToFile);
        nlohmann::json modinfo = nlohmann::json::parse(filereader);



        filereader.close();
    }
}

void Modloader::loadObjectTypesFile(std::string pathToFile){
    if(gameInstance != nullptr){
        std::ifstream filereader;
        filereader.open(":/mods/" + pathToFile);
        nlohmann::json modinfo = nlohmann::json::parse(filereader);



        filereader.close();
    }
}

void Modloader::loadVesselsFile(std::string pathToFile){
    if(gameInstance != nullptr){
        std::ifstream filereader;
        filereader.open(":/mods/" + pathToFile);
        nlohmann::json modinfo = nlohmann::json::parse(filereader);



        filereader.close();
    }
}

std::map<QString, std::string> & Modloader::scanForMods(){
    std::map<QString, std::string> detectedmods = {};

    detectedmods.insert({"Coremod","mods/coremod"});
    /* TBD
    for(auto entry : std::filesystem::recursive_directory_iterator("sandbox")){

    }
    */


    return detectedmods;
}
