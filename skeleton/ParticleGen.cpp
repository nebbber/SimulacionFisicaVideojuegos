#include "ParticleGen.h"

void ParticleGen::setPos(Vector3 p)
{
	pos = p;
}

void ParticleGen::setVel(Vector3 v)
{
	vel = v;
}

void ParticleGen::setDur(double d)
{
	dur = d;
}

void ParticleGen::setProbGen(double pg)
{
	probGen = pg;
}

Vector3 ParticleGen::getPos()
{
	return pos;
}

Vector3 ParticleGen::getVel()
{
	return vel;
}

double ParticleGen::getDur()
{
	return dur;
}

double ParticleGen::getProbGen()
{
	return probGen;
}
