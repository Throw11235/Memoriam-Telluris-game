#include "gascontainer.h"


GasContainer::GasContainer()
{

}

void GasContainer::processContainer(){
    //cut isolated containers for optimization
    if(connectedContainers.size() == 0){
        return;
    }

    float combinedVolume = gases.getVolume();
    float fullInternalEnergy = 0.0;
    GasMix resultingMix = gases;

    //calculate internal energy of container's gases
    for(auto gas : gases.getGases()){
        fullInternalEnergy += gas.first->getMolarHeatCapacity() * gas.second * gases.getTemperature();
    }
    //add combined gas amount to the mix and calculate combined volume of all affected containers
    for(auto iter : connectedContainers){
        combinedVolume += iter->gases.getVolume();

        for(auto gas : iter->gases.getGases()){
            fullInternalEnergy += gas.first->getMolarHeatCapacity() * gas.second * iter->gases.getTemperature();
            resultingMix.changeGasAmount(gas.first, gas.second);
            resultingMix.setMass(resultingMix.getMass() + gas.first->getMolarMass() * gas.second);
        }
    }
    //coefficient of how much gas molecules are transfered to base container and connected ones with equal volume
    float coefficient = gases.getVolume()/combinedVolume;
    resultingMix.setPressure(resultingMix.getPressure() * coefficient);
    resultingMix.setMass(resultingMix.getMass() * coefficient);

    // calculate gas amount and combined heat capacity of gases in a mix
    float heatCapacity = 0.0;
    float molarAmount = 0.0;
    for(auto gas : resultingMix.getGases()){
        gas.second *= coefficient;
        molarAmount += gas.second;
        heatCapacity += gas.first->getMolarHeatCapacity() * gas.second;
    }
    // Calculate resulting temperature by dividing internal energy by heat capacity
    resultingMix.setTemp(fullInternalEnergy / heatCapacity * coefficient);

    //finally calculate pressure based on ideal gas law
    resultingMix.setPressure(R_CONSTANT * resultingMix.getTemperature() * molarAmount / resultingMix.getVolume());
    //Change all connected gas mixes to balanced one
    this->gases = resultingMix;

    for(auto iter : connectedContainers){
        // if volumes are equal just copy the mix
        if(iter->gases.getVolume() == resultingMix.getVolume()){
            iter->gases.copyAnotherMix(resultingMix);
        }
        // if volumes are not equal, multiply gas amount by volume relation
        else{
            float coeff = iter->gases.getVolume() / resultingMix.getVolume();
            iter->gases.copyAnotherMix(resultingMix);

            iter->gases.setMass(iter->gases.getMass()*coeff);
            for(auto gas : iter->gases.getGases()){
                gas.second *= coeff;
            }
        }
    }
}


void GasContainer::connectContainer(GasContainer * newContainer){
    connectedContainers.push_back(newContainer);
}

void GasContainer::disconnectContainer(GasContainer *container){
    connectedContainers.remove(container);
}

GasMix & GasContainer::getGasmix(){
    return gases;
}

std::list<GasContainer *> & GasContainer::getContainers(){
    return connectedContainers;
}
