#include "OscillateWind.h"
#include <cmath>
#include <iostream> 

OscillateWind::OscillateWind(Vector3 velBase, float ks, float k, float amp, float freq)
    : WindGenerator(velBase, ks, k), amplitude(amp), frequency(freq), accumulatedTime(0.0), baseVel(velBase)
{

}

OscillateWind::~OscillateWind()
{
}

void OscillateWind::update(double t, Particle* p)
{
    accumulatedTime += t; // acumula el tiempo

    velViento.x = baseVel.x + amplitude * std::sin(frequency * accumulatedTime);
    velViento.y = baseVel.y + amplitude * std::cos(frequency * accumulatedTime * 0.5); 
    velViento.z = baseVel.z + amplitude * std::sin(frequency * accumulatedTime * 0.7); 

    WindGenerator::update(t, p);
}