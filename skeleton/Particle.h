#pragma once
#include "PxPhysics.h"
#include "PxShape.h"
#include <random>
#include "RenderUtils.hpp"
const float damping = 0.998;
using namespace std;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 c, float time);
	bool integrate(float t);
	bool gettimer();
	void setPos(Vector3 Pos);
	physx::PxTransform getPos();
	void setVel(Vector3 Vel);
	void setCol(Vector4 Col);
	void settime(float t);
	Vector3 getVel();
	virtual ~Particle();
	Vector3 vel;
	float timer = 0;
	float time;
	unsigned _type;

protected:
	
	int masa;
	Vector3 acelera;
	Vector4 color;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

