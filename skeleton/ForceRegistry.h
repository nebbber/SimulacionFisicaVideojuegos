#pragma once
class ForceGenerator;
class Particle;
#include<vector>
class ForceRegistry
{
private:
	struct info
	{
		ForceGenerator* fg;
		Particle* p;
	};

	std::vector<info> registro;

public:
	 ForceRegistry();
	 ~ForceRegistry();
	void addGeneratorToParticle(ForceGenerator* forcg, Particle* pr);
	void removeGeneratorToParticle(ForceGenerator* forcg, Particle* pr);
	void updateForces(double t);
	bool isEmpty() const ;
};

