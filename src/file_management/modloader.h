#ifndef MODLOADER_H
#define MODLOADER_H


#include <src/game.h>
#include <nlohmann/json.hpp>

class Modloader
{
    Game * gameInstance = nullptr;
public:
    Modloader(Game * toConnect);

    //returns mod name/file pairs for all modinfo jsons in ~/mods
    std::map<QString, std::string> & scanForMods();

    void loadMods();

    void loadIndividualMod(std::string pathToFile);

    void loadObjectTypesFile(std::string pathToFile);

    void loadVesselsFile(std::string pathToFile);


};

#endif // MODLOADER_H
