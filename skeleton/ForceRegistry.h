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

    // Mapa: Rígido -> Lista de generadores
    std::unordered_map<PxRigidDynamic*, std::vector<ForceGenerator*>> rigidToGenerators;

    // Mapa: Generador -> Lista de rígidos
    std::unordered_map<ForceGenerator*, std::vector<PxRigidDynamic*>> generatorToRigids;

public:
    // Añadir relación partícula-generador
    void add(Particle* p, ForceGenerator* fg);

    //para solidos
    void add(PxRigidDynamic* r, ForceGenerator* fg);
    void remove(PxRigidDynamic* r, ForceGenerator* fg);
    void removeRigid(PxRigidDynamic* r);

    // Eliminar una relación específica
    void remove(Particle* p, ForceGenerator* fg);

    // Eliminar todas las asociaciones de un generador
    void removeGenerator(ForceGenerator* fg);

    // Eliminar todas las asociaciones de una partícula
    void removeParticle(Particle* p);


    // Actualizar todas las fuerzas
    void update(float duration);
};