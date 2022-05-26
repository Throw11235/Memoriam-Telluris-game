#include "gas.h"

Gas::Gas()
{

}

float Gas::getMolarMass(){
    return molarMass;
}

float Gas::getMolarHeatCapacity(){
    return molarHeatCap;
}

std::string Gas::getGasName(){
    return name;
}

void Gas::setGasName(std::string newName){
    name = newName;
}

void Gas::setMolarMass(float newMolMass){
    molarMass = newMolMass;
}

void Gas::setMolarHeatCapacity(float newMolHeat){
    molarHeatCap = newMolHeat;
}
