#include "Particle.h"
#include <iostream>

Particle::Particle(double Time,Vector3 Pos, Vector3 Vel, Vector3 Acc, float d, float m, Vector4 Color,float siz):size(siz), masa(1.0f), fuerzaAcum (0,0,0),tipo(1)

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
	h = 1.0f;
	w = 1.0f;
	p = 1.0f;
}
void Particle::setH(float _h)
{
	h = _h;
}
void Particle::setW(float _w)
{
	w = _w;
}
void Particle::setP(float _p)
{
	p = _p;
}

float Particle::getH()
{
	return h;
}
float Particle::getW()
{
	return w;
}
float Particle::getP()
{
	return p;
}

void Particle::setShape(int i)
{
	tipo = i;
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
void Particle::setMasa(float m)
{
	masa += m;
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
	if (tipo == 1)
	{
		PxShape* shShape = CreateShape(PxSphereGeometry(size));
		renderItem = new RenderItem(shShape, pose, color);
	}
	else
	{
		PxShape* shShape = CreateShape(PxBoxGeometry(PxVec3(h,w,p)));
		renderItem = new RenderItem(shShape, pose, color);
	}

	
		
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
