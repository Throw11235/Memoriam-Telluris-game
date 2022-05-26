#ifndef GASCONTAINER_H
#define GASCONTAINER_H
#include <src/atmospherics/gasmix.h>
#include <list>

class GasContainer
{

protected:
    GasMix gases;
    std::list<GasContainer*> connectedContainers = {};

public:
    void connectContainer(GasContainer* newContainer);
    void disconnectContainer(GasContainer * container);

    GasMix & getGasmix();
    std::list<GasContainer*> & getContainers();

    virtual void processContainer();

    GasContainer();
};

#endif // GASCONTAINER_H
