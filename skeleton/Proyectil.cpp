#include "Proyectil.h"

Proyectil::Proyectil()
{
}

void Proyectil::shoot(Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mR, float g, PxVec3 dir)
{
	double energiaR = 0.5 * mR * pow(VelR.magnitude(),2);
	//pq Es=Er
	float masaS = energiaR / pow(VelR.magnitude(), 2) * 2;

	//Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mS, float mR, float g
	Particle* p= new Particle(Pos,VelS,VelR,Acc,d,masaS,mR,g);
	//p->integrate();

}
