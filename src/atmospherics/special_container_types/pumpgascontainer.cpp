#include "pumpgascontainer.h"

PumpGasContainer::PumpGasContainer()
{

}

void pumpGasesInaMix(GasContainer * pumpedContainer, GasMix * targetMix, float & requiredMass){

    if(pumpedContainer->getGasmix().getMass() >= requiredMass){
        // Subtract mass of gases from required one
        requiredMass -= pumpedContainer->getGasmix().getMass();

        //increase target mix mass before setting pumped mix to vacuum
        targetMix->setMass(targetMix->getMass() + pumpedContainer->getGasmix().getMass());

        //calculate transfered internal energy and nullify molar amount of each gas
        float transferedEnergy = 0.0;
        for(auto gas : pumpedContainer->getGasmix().getGases()){
            targetMix->changeGasAmount(gas.first, gas.second);
            transferedEnergy += pumpedContainer->getGasmix().getTemperature() * gas.second * gas.first->getMolarHeatCapacity();
            gas.second = 0;
        }

        // set gas mix parameters to vacuum
        pumpedContainer->getGasmix().setPressure(0);
        pumpedContainer->getGasmix().setTemp(0);
        pumpedContainer->getGasmix().setMass(0);

        //Calculate thermodynamic parameters of the target mix  before heat transfer
        float targetHeatCap = 0.0;
        float targetIntEnergy = 0.0;
        float molarAmount = 0.0;
        for(auto gas : targetMix->getGases()){
            molarAmount += gas.second;
            float gasHeatCap = gas.first->getMolarHeatCapacity() * gas.second;
            targetHeatCap += gasHeatCap;
            targetIntEnergy += gasHeatCap * targetMix->getTemperature();
        }

        //Calculate resulting temperature and pressure
        targetMix->setTemp((targetIntEnergy + transferedEnergy)*targetHeatCap);
        targetMix->setPressure(R_CONSTANT * targetMix->getTemperature() * molarAmount / targetMix->getVolume());

        //Look for non-vacuum connected containers
        std::list<GasContainer*> notVisitedContainers = {};
        for(auto container : pumpedContainer->getContainers()){
            if(container->getGasmix().getPressure() != 0){
                notVisitedContainers.push_back(container);
            }
        }
        //recursively apply this function to said containers
        for(auto container : notVisitedContainers){
            pumpGasesInaMix(container, targetMix, requiredMass);
        }
        //Let gas flow back
        pumpedContainer->processContainer();
    }
    else if(requiredMass != 0){
        //nullify required mass to stop recursive function from making extra steps
        requiredMass = 0;

        // proportion of how much mass is removed from gasmix
        float coefficient = requiredMass / pumpedContainer->getGasmix().getMass();

        //thermodynamic properties of a pumped gas
        float transferedEnergy = 0.0;
        float pumpedHeatCap = 0.0;

        //Constant from PV/T = const equation, used to optimize calculation of pumped mix pressure
        float newConst = (1 - coefficient) * pumpedContainer->getGasmix().getPressure() * pumpedContainer->getGasmix().getVolume() /  pumpedContainer->getGasmix().getTemperature();

        //transfer gas moles to a target mix and calculate new masses
        for(auto gas : pumpedContainer->getGasmix().getGases()){
            targetMix->changeGasAmount(gas.first, gas.second * coefficient);
            transferedEnergy += gas.first->getMolarHeatCapacity() * targetMix->getTemperature() * gas.second * coefficient;
            pumpedContainer->getGasmix().changeGasAmount(gas.first, gas.second * coefficient *  -1);
            pumpedHeatCap += gas.first->getMolarHeatCapacity() * gas.second;
        }
        targetMix->setMass(targetMix->getMass() + pumpedContainer->getGasmix().getMass() * coefficient);
        pumpedContainer->getGasmix().setMass(pumpedContainer->getGasmix().getMass() * (1 - coefficient));

        //Calculate thermodynamic parameters of the target mix  before heat transfer
        float targetHeatCap = 0.0;
        float targetIntEnergy = 0.0;
        float molarAmount = 0.0;
        for(auto gas : targetMix->getGases()){
            molarAmount += gas.second;
            float gasHeatCap = gas.first->getMolarHeatCapacity() * gas.second;
            targetHeatCap += gasHeatCap;
            targetIntEnergy += gasHeatCap * targetMix->getTemperature();
        }

        //Calculate temperature from thermodynamic laws
        pumpedContainer->getGasmix().setTemp(pumpedContainer->getGasmix().getTemperature() - transferedEnergy * pumpedHeatCap);
        targetMix->setTemp((targetIntEnergy + transferedEnergy)*targetHeatCap);

        //Calculate mixtures pressure from ideal gas law
        targetMix->setPressure(R_CONSTANT * targetMix->getTemperature() * molarAmount / targetMix->getVolume());
        pumpedContainer->getGasmix().setPressure(newConst * pumpedContainer->getGasmix().getTemperature() / pumpedContainer->getGasmix().getVolume());

        //allows gases to flow back
        pumpedContainer->processContainer();
    }
}


void PumpGasContainer::processContainer(){

    if(!pumping || connectedContainers.size() == 0 || pumpTarget == nullptr){
        return;
    }

    GasMix * targetMix = new GasMix;
    *targetMix = this->pumpTarget->getGasmix();
    float & requiredsize = this->pumpingPower;

    for(auto container : this->getContainers()){
        pumpGasesInaMix(container, targetMix, requiredsize);
    }

    this->pumpTarget->processContainer();
}
