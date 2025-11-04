#include "Particle.h"
#include <iostream>

Particle::Particle(double Time,Vector3 Pos, Vector3 Vel, Vector3 Acc, float d, float m, Vector4 Color,float size):size(size), masa(1.0f), fuerzaAcum (0,0,0)

{
	pose = new PxTransform(Pos);
	
	
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

	acc = fuerzaAcum / masa;
	
	pose->p = pose->p + t * vel;
	vel = vel + t * acc;

	vel = vel * pow(dumping,t); //v=v*d elevado a el t

	dur -= t;

	
	if (dur <= 0.0) {
		alive = false;
	}

	fuerzaAcum = { 0,0,0 };
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
	size(other.size),
	masa(other.masa)
{
	fuerzaAcum = other.fuerzaAcum;
	masa = other.masa;
	pose = new PxTransform(other.pose->p);
	
	initialPose = other.initialPose;
}

void Particle::setGeometry()
{
	PxShape* shShape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shShape, pose, color);
		
}

float Particle::getMasa() const
{
	return masa;
}

Vector3 Particle::getVel() const
{
	return vel;
}

Vector3 Particle::getPos() const
{
	return Vector3(pose->p.x, pose->p.y, pose->p.z);
}

void Particle::addForce(Vector3 f)
{
	fuerzaAcum += f;
}
