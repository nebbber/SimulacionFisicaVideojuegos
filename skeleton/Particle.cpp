#include "Particle.h"
#include <iostream>


Particle::Particle(double Time,Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mS, float mR, Vector4 color)
{
	pose = new PxTransform(Pos);
	velR =  VelR;

	PxSphereGeometry geo = PxSphereGeometry(); //creamos geometria
	geo.radius = 5;
	PxShape* sphere = CreateShape(geo);//creamos forma

	renderItem = new RenderItem(sphere, pose, color);//renderizamos item
	RegisterRenderItem(renderItem);//registramos el item a renderizar

	this->acc = Acc;
	initialPose = Pos - VelS;
	dumping = d;//de 0 a 1

	masaR = mR;
	masaS = mS;
	velS = VelS;
	alive = true;
	time = Time;
}

Particle::~Particle()
{
	
	DeregisterRenderItem(renderItem);  
	delete pose;  

	//recordad que tendréis que deregistrar el objeto RenderItem de la escena en el destructor de la partícula.
}

void Particle::integrate(double t)
{
	//EULER

	
	pose->p = pose->p + t * velS;
	velS = velS + t * acc;

	velS = velS * pow(dumping,t); //v=v*d elevado a el t


	time -= t;

	
	if (time <= 0.0) {
		alive = false;
	}
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

bool Particle::isAlive()
{
	return alive;
}
