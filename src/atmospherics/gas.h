#ifndef GAS_H
#define GAS_H
#include <string>

class Gas
{
    std::string name = "";
    float molarMass = 0.0;
    float molarHeatCap = 0.0;

public:
    Gas();

    float getMolarMass();
    void setMolarMass(float newMolMass);

    float getMolarHeatCapacity();
    void setMolarHeatCapacity(float newMolHeat);

    std::string getGasName();
    void setGasName(std::string newName);
};

#endif // GAS_H
