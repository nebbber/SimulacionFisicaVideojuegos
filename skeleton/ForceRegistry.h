#pragma once
#include <map>
#include <vector>
#include <string>
#include "Particle.h"
#include "ForceGenerator.h"

struct ParticleForceEntry {
    Particle* particle;
    ForceGenerator* fg;
    bool active = true;  // Por defecto, la fuerza está activa
};

class ForceRegistry {
private:
    // Map de grupo -> lista de fuerzas y partículas
    std::map<std::string, std::vector<ParticleForceEntry>> _registries;

public:
    ForceRegistry() = default;
    ~ForceRegistry() = default;

    void addParticle(Particle* p, const std::string& groupName);

    // Nuevo método
    void addGeneratorToParticle(const std::string& groupName, ForceGenerator* fg, Particle* p);

    void setForceActiveForGroup(const std::string& groupName, ForceGenerator* fg, bool active);

    void updateForces(double t);
};