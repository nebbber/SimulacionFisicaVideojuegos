#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class BreathWater;
class muelleMovible : public ParticleSystem
{
private:
	BreathWater* BreathWaterSys = nullptr;
	Particle* particulaMovible;
	Particle* p2Muelles;

	float speed;
	float rightLimit;
	float leftLimit;
	bool _isMovingRight = true;
	bool active = true;

public:
	muelleMovible(Gravity* g, Vector3 startPos);

	void update(double t) override;
	~muelleMovible();
	void setPosMovible(Vector3 pos);
	void setK(int K);
	Vector3 getPos();
	float getRadius() const;
	void deactivate();

};

