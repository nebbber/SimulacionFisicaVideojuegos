#include "ForceRegistry.h"

void ForceRegistry::addGeneratorToParticle(const std::string& groupName, ForceGenerator* fg, Particle* p) {
    if (!p || !fg) return;

    ParticleForceEntry entry;
    entry.particle = p;
    entry.fg = fg;

    _registries[groupName].push_back(entry);
}
void ForceRegistry::setForceActiveForGroup(const std::string& groupName, ForceGenerator* fg, bool active) {
    auto it = _registries.find(groupName);
    if (it != _registries.end()) {
        for (auto& entry : it->second) {
            if (entry.fg == fg) {
                entry.active = active;
            }
        }
    }
}
void ForceRegistry::updateForces(double t) {
    for (auto& group : _registries) {
        for (auto& entry : group.second) {
            if (entry.active && entry.particle && entry.fg) {
                entry.fg->update(t,entry.particle);
            }
        }
    }
}