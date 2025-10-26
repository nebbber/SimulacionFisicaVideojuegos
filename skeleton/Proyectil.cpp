#include "Proyectil.h"
#include <iostream>
Proyectil::Proyectil()
{
	empty = false;
}

void Proyectil::createBullet(Vector3 Pos, double VelS, Vector3 VelR, Vector3 Acc, float d, float mR, PxVec3 dir, Vector4 color)
{
	double energiaR = 0.5 * mR * pow(VelR.magnitude(),2);
	//pq Es=Er
	float masaS = energiaR / pow(VelR.magnitude(), 2) * 2;

	Vector3	vel(dir*VelS);
	Particle* p= new Particle(0.0,Pos,vel,Acc,d,masaS,color,1.0f);
	p->setGeometry();
	bullets.push_back(p);

}

bool Proyectil::isEmpty()
{
	return bullets.empty();
}

void Proyectil::shot(double t)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->integrate(t);
	}
}

Proyectil::~Proyectil()
{
	for (Particle *p: bullets)
	{
		delete p;
	}
	
	bullets.clear();
}



