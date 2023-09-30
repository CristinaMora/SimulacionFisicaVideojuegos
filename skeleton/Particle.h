#pragma once
#include "PxPhysics.h"
#include "PxShape.h"

#include "RenderUtils.hpp"
const float damping = 0.998;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 color);
	void integrate(float t);
	float gettimer();

private:
	float timer=0;
	int masa;
	Vector3 acelera;
	Vector3 vel;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

