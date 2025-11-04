#pragma once
#include "ForceGenerator.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include <vector>
#include <string>

class ForceRegistry
{
private:
    struct ForceEntry
    {
        ForceGenerator* fg;
        Particle* p;
    };

    struct ForceGroup
    {
        ParticleSystem* system;
        std::string groupName;  
        std::vector<ForceEntry> entries;
    };

    std::vector<ForceGroup> groups;

public:
    ForceRegistry();
    ~ForceRegistry();

    void addGeneratorToParticle(ParticleSystem* sys, const std::string& groupName, ForceGenerator* fg, Particle* p);
    void removeGeneratorFromParticle(ParticleSystem* sys, const std::string& groupName, ForceGenerator* fg, Particle* p);
    void updateForces(double t);
    void clearSystem(ParticleSystem* sys);
    bool isEmpty() const;
    const std::vector<ForceGroup>& getGroups() const { return groups; }
};