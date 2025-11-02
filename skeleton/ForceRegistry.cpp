#include "ForceRegistry.h"

 ForceRegistry::ForceRegistry()
{
}

 ForceRegistry::~ForceRegistry()
{
}

 void ForceRegistry::addGeneratorToParticle(ForceGenerator* forcg, Particle* pr)
{
	 info inf;
	 inf.fg = forcg;
	 inf.p = pr;
	 registro.push_back(inf);
}

 void ForceRegistry::removeGeneratorToParticle(ForceGenerator* forcg, Particle* pr)
{

}

 void ForceRegistry::updateForces(double t)
{

		 for (auto &e : registro)
		 {
			 e.fg->update(t, e.p);
		 }
	 
}
