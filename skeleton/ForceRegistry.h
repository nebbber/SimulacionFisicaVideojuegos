#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Particle.h"
#include "ForceGenerator.h"

class ForceRegistry {
private:
    // Mapa: Partícula -> Lista de generadores
    std::unordered_map<Particle*, std::vector<ForceGenerator*>> particleToGenerators;

    // Mapa: Generador -> Lista de partículas
    std::unordered_map<ForceGenerator*, std::vector<Particle*>> generatorToParticles;

public:
    // Añadir relación partícula-generador
    void add(Particle* p, ForceGenerator* fg);

    // Eliminar una relación específica
    void remove(Particle* p, ForceGenerator* fg);

    // Eliminar todas las asociaciones de un generador
    void removeGenerator(ForceGenerator* fg);

    // Eliminar todas las asociaciones de una partícula
    void removeParticle(Particle* p);

    // Actualizar todas las fuerzas
    void update(float duration);
};