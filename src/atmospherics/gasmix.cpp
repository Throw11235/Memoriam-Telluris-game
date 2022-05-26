#include "gasmix.h"

GasMix::GasMix()
{

}

void GasMix::recalcMass(){
    mass = 0;
    for(auto iter : gasesInAMix){
        mass += iter.first->getMolarMass() * iter.second;
    }
}

void GasMix::setPressure(float newPressure){
    pressure = newPressure;
}

void GasMix::setTemp(float newTemp){
    temperature = newTemp;
}

void GasMix::setMass(float newMass){
    mass = newMass;
}

void GasMix::setVolume(float newVolume){
    volume = newVolume;
}

float GasMix::getMass(){
    return mass;
}

float GasMix::getPressure(){
    return pressure;
}

float GasMix::getTemperature(){
    return temperature;
}

float GasMix::getVolume(){
    return volume;
}

void GasMix::changeGasAmount(Gas *gas, float newAmount){
    std::unordered_map<Gas*, float>::iterator iter  = gasesInAMix.find(gas);
    if(iter != nullptr){
        iter->second += newAmount;
    }
    else{
        gasesInAMix.insert({gas,newAmount});
    }
}

std::unordered_map<Gas *, float> & GasMix::getGases(){
    return gasesInAMix;
}


//copy contents of one mix to another assuming same volume
void GasMix::copyAnotherMix(GasMix &gasMix){
    temperature = gasMix.getTemperature();
    pressure = gasMix.getPressure();
    mass = gasMix.getMass();
    gasesInAMix = gasMix.gasesInAMix;
}
