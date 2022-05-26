#ifndef PUMPGASCONTAINER_H
#define PUMPGASCONTAINER_H
#include <src/atmospherics/gascontainer.h>

class PumpGasContainer : public GasContainer
{
    bool pumping = false;
    float pumpingPower = 0.0; // in Watts, used to calculate throughput

    GasContainer * pumpTarget;
public:

    void processContainer() override;

    PumpGasContainer();
};

#endif // PUMPGASCONTAINER_H
