#ifndef EXTERNALGASCONTAINER_H
#define EXTERNALGASCONTAINER_H
#include <src/atmospherics/gascontainer.h>

class ExternalGasContainer : public GasContainer
{
    GasMix & externalMix;
public:

    void processContainer() override;

    void setNewExternalGases(GasMix & newexternalMix);

    ExternalGasContainer(GasMix & externalMix);
};

#endif // EXTERNALGASCONTAINER_H
