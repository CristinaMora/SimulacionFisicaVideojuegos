#pragma once
#include "PxPhysics.h"
#include "PxShape.h"

#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
		void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;// desregistrar el objeto
};

