#pragma once
#include "PxShape.h"
#include "RenderUtils.hpp"
#include <iostream>
#include <random>
const float damping = 0.99;
using namespace std;
using namespace physx;

class Particle
{
public:
	
	Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, double mas, Vector4 c, float t, Vector3 tam, int type);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, double mas, Vector4 c, float time, float radio, int type);

	bool integrate(float t);
	void clearForce();
	void addForce(const Vector3 f);
	void setPos(Vector3 Pos);
	Vector3 getPos();
	void setVel(Vector3 Vel);
	Vector3 getVel();
	bool getAlive();
	void settime(float t);
	void setCol(Vector4 Col);
	double getMass();
	int getType();
	virtual ~Particle();
	


protected:
	Vector3 vel;
	float timer = 0;
	float time;
	int _type;
	double masa;
	// Accumulated force
	Vector3 _force_accum;
	Vector3 acelera;
	Vector4 color;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

