#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <vector>
using namespace std;
using namespace physx;
class Particle
{
private:
	
	Vector3 vel;
	float masa;
	Vector3 acc;
	physx::PxTransform* pose; // A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;
	Vector3 initialPose;
	float dumping;
	bool alive;
	double dur;
	Vector4 color;
	Vector3 fuerzaAcum;
	int tipo;
	float size;
	int h;

public:
	Particle(const Particle& other);
	Particle(double time,Vector3 Pos, Vector3 Vel, Vector3 Acc, float d, float m, Vector4 Color, float siz);
	void setShape(int i);
	~Particle();

	void integrate(double t);
	void semi(double t);
	void verlet(double t);
	bool isAlive();
	void setColor(Vector4 Color);

	void setPos(Vector3 p);
	void setVel(Vector3 v);
	void setDur(double t);
	void setGeometry();
	float getMasa() const;
	Vector3 getVel() const;
	Vector3 getPos() const;
	void addForce(Vector3 f);
	Particle* clone() const;

	float getHeight();
};