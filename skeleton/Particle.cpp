#include "Particle.h"
#include <iostream>


Particle::Particle(double Time,Vector3 Pos, Vector3 Vel, Vector3 Acc, float d, float m, Vector4 Color,float size)

{
	pose = new PxTransform(Pos);
	

	/*PxSphereGeometry geo = PxSphereGeometry(); //creamos geometria
	geo.radius = 5;
	PxShape* sphere = CreateShape(geo);//creamos forma

	
	renderItem = new RenderItem(sphere, pose, color);//renderizamos item
	RegisterRenderItem(renderItem);//registramos el item a renderizar
	*/
	color = Color;
	this->acc = Acc;
	initialPose = Pos - Vel;
	dumping = d;//de 0 a 1


	masa = m;
	vel = Vel;
	alive = true;
	dur = Time;

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);  
	delete pose; 
}

void Particle::integrate(double t)
{
	//EULER

	
	pose->p = pose->p + t * vel;
	vel = vel + t * acc;

	vel = vel * pow(dumping,t); //v=v*d elevado a el t

	dur -= t;

	
	if (dur <= 0.0) {
		alive = false;
	}
}

void Particle::semi(double t)
{
	//SEMI-IMPLICITO
	vel = vel + t * acc;
	pose->p = pose->p + t * vel;

	vel = vel * pow(dumping, t); //v=v*d elevado a el t
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

void Particle::setColor(Vector4 Color)
{
	color = Color;
}

void Particle::setPos(Vector3 p)
{
	pose->p = p;
}

void Particle::setVel(Vector3 v)
{
	vel = v;
}

void Particle::setDur(double t)
{
	dur = t;
}

Particle* Particle::clone() const
{
	return new Particle(*this);
	
}
Particle::Particle(const Particle& other) :
	vel(other.vel),
	acc(other.acc),
	dumping(other.dumping),
	dur(other.dur),
	renderItem(nullptr),  
	color(other.color),
	masa(other.masa),
	size(other.size)
{
	
	pose = new PxTransform(other.pose->p);
	
	initialPose = other.initialPose;
}

void Particle::setGeometry()
{
	if (renderItem == nullptr) {
		PxShape* shShape = CreateShape(PxSphereGeometry(1));
		renderItem = new RenderItem(shShape, pose, color);
	}
}