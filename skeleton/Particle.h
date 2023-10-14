#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include <random>
#include "RenderUtils.hpp"
const float damping = 0.998;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 c, bool render);
	void integrate(float t);
	float gettimer();
	Particle* clone();
	void setPos(Vector3 Pos);
	physx::PxTransform getPos();
	void setVel(Vector3 Vel);
	Vector3 getVel();
	virtual ~Particle();
	Vector3 vel;
	float timer = 0;

private:
	
	int masa;
	Vector3 acelera;
	Vector4 color;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

