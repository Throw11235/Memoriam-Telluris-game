#ifndef GASMIX_H
#define GASMIX_H
#include <map>
#include <unordered_map>
#include <src/atmospherics/gas.h>
#define R_CONSTANT 8.31446261815324

class GasMix
{
    float pressure = 0.0; // in Pascal
    float temperature = 0.0; // in Kelvin
    float volume = 0.0; // in cubic meters
    float mass = 0.0; // in grams

    std::unordered_map<Gas*, float> gasesInAMix; //gas type and molar amount pairs
public:
    GasMix();

    void setPressure(float newPressure);
    void setVolume(float newVolume);
    void setTemp(float newTemp);
    void setMass(float newMass);
    void recalcMass();

    std::unordered_map<Gas*, float> & getGases();

    void copyAnotherMix(GasMix & gasMix);
    void changeGasAmount(Gas* gas, float newAmount);


    float getPressure();
    float getTemperature();
    float getVolume();
    float getMass();
};

#endif // GASMIX_H
