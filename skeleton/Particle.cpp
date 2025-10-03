#include "Particle.h"
#include <iostream>

using namespace std;
using namespace physx;

Particle::Particle(Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mS, float mR, float g)
{
	pose = new PxTransform(Pos);
	velS = VelS;
	velR = VelR;

	PxSphereGeometry geo = PxSphereGeometry(); //creamos geometria
	geo.radius = 5;
	PxShape* sphere = CreateShape(geo);//creamos forma

	renderItem = new RenderItem(sphere, pose, Vector4(1, 1, 1, 1));//renderizamos item
	RegisterRenderItem(renderItem);//registramos el item a renderizar

	acc = Acc;
	initialPose = Pos - VelS;
	dumping = d;//de 0 a 1

	masaR = mR;
	masaS = mS;
	gravedad = g;
	
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	//recordad que tendréis que deregistrar el objeto RenderItem de la escena en el destructor de la partícula.
}

void Particle::integrate(double t)
{
	//EULER
	pose->p = pose->p + t * velS;
	velS = velS + t * acc;

	velS = velS * pow(dumping,t); //v=v*d elevado a el t
}

void Particle::semi(double t)
{
	//SEMI-IMPLICITO
	velS = velS + t * acc;
	pose->p = pose->p + t * velS;

	velS = velS * pow(dumping, t); //v=v*d elevado a el t
}

void Particle::verlet(double t)
{
	//VERLET
	Vector3 now = pose->p;
	pose->p = 2 * pose->p - initialPose +t * t * acc;
	initialPose = now;
}
