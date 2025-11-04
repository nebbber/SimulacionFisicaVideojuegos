#include "ParticleGen.h"

ParticleGen::ParticleGen(std::string nam): _name(nam), _u(0.0, 1.0), pModelo(nullptr)
{
	_mt = std::mt19937(std::random_device{}());
	
}
ParticleGen::~ParticleGen()
{

}
void ParticleGen::setPosMedia(Vector3 p)
{
	posMedia = p;
}

void ParticleGen::setVelMedia(Vector3 v)
{
	velMedia = v;
}

void ParticleGen::setDurMedia(double d)
{
	durMedia = d;
}

void ParticleGen::setProbGen(double pg)
{
	probGen = pg;
}

void ParticleGen::setNumParticles(int n)
{
	n_particles = n;
}

void ParticleGen::setModelo(Particle* p)
{
	//if (pModelo != nullptr) { delete pModelo; }
	pModelo = p;
}

int ParticleGen::getNumParticles()
{
	return n_particles;
}

Vector3 ParticleGen::getPosMedia()
{
	return posMedia;
}

Vector3 ParticleGen::getVelMedia()
{
	return velMedia;
}

double ParticleGen::getDurMedia()
{
	return durMedia;
}

double ParticleGen::getProbGen()
{
	return probGen;
}

std::string ParticleGen::getName() const
{
	return _name;
}

void ParticleGen::changeActivation()
{
	isActive = !isActive;
}
