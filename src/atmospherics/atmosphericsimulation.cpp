#include "atmosphericsimulation.h"

AtmosphericSimulation::AtmosphericSimulation()
{

}

void AtmosphericSimulation::updateSimulation(){
    for(auto iter : atmosContainers){
        iter->processContainer();
    }
}

void AtmosphericSimulation::addContainer(GasContainer *newContainer){
    atmosContainers.push_back(newContainer);
}

void AtmosphericSimulation::removeContainer(GasContainer *container){
    atmosContainers.remove(container);
}
