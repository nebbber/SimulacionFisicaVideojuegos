#include "ForceRegistry.h"
#include <algorithm>

ForceRegistry::ForceRegistry() = default;

ForceRegistry::~ForceRegistry() {
    groups.clear();
}

// Añadir fuerza a un grupo específico dentro de un sistema de partículas
void ForceRegistry::addGeneratorToParticle(ParticleSystem* sys, const std::string& groupName, ForceGenerator* fg, Particle* p)
{
    for (auto& g : groups) {
        if (g.system == sys && g.groupName == groupName) {
            g.entries.push_back({ fg, p });
            return;
        }
    }

    // Si no existe, crear grupo nuevo
    ForceGroup g;
    g.system = sys;
    g.groupName = groupName;
    g.entries.push_back({ fg, p });
    groups.push_back(g);


}

void ForceRegistry::removeGeneratorFromParticle(ParticleSystem* sys, const std::string& groupName, ForceGenerator* fg, Particle* p)
{
    for (auto& g : groups) {
        if (g.system == sys && g.groupName == groupName) {
            auto& e = g.entries;
            e.erase(std::remove_if(e.begin(), e.end(),
                [fg, p](const ForceEntry& fe) { return fe.fg == fg && fe.p == p; }),
                e.end());
            return;
        }
    }
}

void ForceRegistry::updateForces(double t) {
    for (auto& g : groups) {
        for (auto& e : g.entries) {
                e.fg->update(t, e.p);
            
        }
    }
}

void ForceRegistry::clearSystem(ParticleSystem* sys)
{
    groups.erase(std::remove_if(groups.begin(), groups.end(),
        [sys](const ForceGroup& g) { return g.system == sys; }),
        groups.end());
}

bool ForceRegistry::isEmpty() const
{
    for (const auto& g : groups)
        if (!g.entries.empty()) return false;
    return true;
}