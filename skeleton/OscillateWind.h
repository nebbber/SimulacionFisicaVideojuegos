#pragma once
#include "WindGenerator.h"

class OscillateWind : public WindGenerator
{
protected:
    float amplitude;   
    float frequency;   
    double accumulatedTime;
    Vector3 baseVel;
public:
 
    OscillateWind(Vector3 velBase, float ks, float k, float amp, float freq);

     ~OscillateWind();

   
    virtual void update(double t, Particle* p) override;
};