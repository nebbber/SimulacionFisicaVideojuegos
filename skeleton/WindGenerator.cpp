#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3 vel, float ks, float k):velViento(0,0,0),k1(0.0f),k2(0.0f)
{
	velViento = vel;
	k1 = ks;
	k2 = k;

}

WindGenerator::~WindGenerator()
{
}

void WindGenerator::update(double t, Particle* p)
{
	Vector3 diff = velViento - p->getVel();

	// modulo 
	float v = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

	Vector3 f  = k1 * diff + k2 * v * diff;
	p->addForce(f);
	
}
void WindGenerator::update(double t, PxRigidDynamic* r)
{
	if (!r) return;

	PxVec3 currentVel = r->getLinearVelocity();
	PxVec3 targetVel(velViento.x, velViento.y, velViento.z);

	PxVec3 diff = targetVel - currentVel;
	float v = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

	PxVec3 force = k1 * diff + k2 * v * diff;


	r->addForce(force);
}