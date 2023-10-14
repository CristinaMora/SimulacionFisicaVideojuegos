#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include <random>
#include "RenderUtils.hpp"
const float damping = 0.998;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 color);
	void integrate(float t);
	float gettimer();
	void setPos(Vector3 Pos);
	physx::PxTransform getPos();
	~Particle();
	Vector3 vel;
	float timer = 0;

private:
	
	int masa;
	Vector3 acelera;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

