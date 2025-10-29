#include "ForceRegistry.h"
#include"ForceGenerator.h"
#include "Particle.h"
constexpr int NUM = 1000;
 ForceRegistry::ForceRegistry()
{
}

 ForceRegistry::~ForceRegistry()
{
}

 void ForceRegistry::addGeneratorToParticle(ForceGenerator* forcg, Particle* pr)
{
	 info p;
	 p.fg = forcg;
	 p.p = pr;
	 registro.push_back(p);
}

 void ForceRegistry::removeGeneratorToParticle(ForceGenerator* forcg, Particle* pr)
{

}

 void ForceRegistry::updateForces(double t)
{

		 for (auto e : registro)
		 {
			 e.fg->update(t, e.p);
		 }
	 
}
