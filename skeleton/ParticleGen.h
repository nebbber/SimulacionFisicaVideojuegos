#pragma once
#include <random>
#include "core.hpp"
#include "Particle.h"
#include <list>
#include <string>
class ParticleGen
{
private:
	

protected:
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u; //de 0 a 1 porb de generar particula lo tienen todas en la uniforme utiliza
	//tambien esta para la vel, pos...
	// esto tiene que ir en la particula y se le asigna cuendo creas en generate p
	//Vector3 pos;
	//Vector3 vel;
	//double dur;
	double probGen;
	int n_particles;
	Vector3 posMedia;
	Vector3 velMedia;
	double durMedia;
	Particle* pModelo;
	
	std::string _name;
public:
	ParticleGen(std::string nam);

	~ParticleGen();
	virtual list<Particle*> generateP() = 0;
	void setPosMedia( Vector3 p);
	void setVelMedia(Vector3 v);
	void setDurMedia(double d); //duracion
	void setProbGen(double pg);//probabilidad de generacion
	void setNumParticles(int n);

	void setModelo(Particle* p);
	//poner setters y geter del num de particulas
	int getNumParticles();
	Vector3 getPosMedia();
	Vector3 getVelMedia();
	double getDurMedia();
	double getProbGen();
	std::string getName() const;
	void setActive(bool a);
	bool getActive();
};