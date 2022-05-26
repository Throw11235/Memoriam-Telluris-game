#include "externalgascontainer.h"

ExternalGasContainer::ExternalGasContainer(GasMix & externalMix) : externalMix(externalMix)
{
    this->externalMix = externalMix;
}

void ExternalGasContainer::processContainer(){
    this->gases = externalMix;
    for(auto container : this->connectedContainers){
        container->processContainer();
    }
}

void ExternalGasContainer::setNewExternalGases(GasMix & newexternalMix){
    this->externalMix = newexternalMix;
    this->processContainer();
}
