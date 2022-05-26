#ifndef ATMOSPHERICSIMULATION_H
#define ATMOSPHERICSIMULATION_H
#include <src/atmospherics/gascontainer.h>

class AtmosphericSimulation
{
    std::list<GasContainer*> atmosContainers = {};
public:
    void addContainer(GasContainer* newContainer);
    void removeContainer(GasContainer * container);

    void updateSimulation();

    AtmosphericSimulation();
};

#endif // ATMOSPHERICSIMULATION_H
