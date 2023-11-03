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
	Particle(Vector3 Pos, Vector3 Vel,Vector3 aceler, int mas,Vector4 c, float time, float radio, int type);
	bool integrate(float t);
	bool gettimer();
	void setPos(Vector3 Pos);
	physx::PxTransform getPos();
	void setVel(Vector3 Vel);
	void setCol(Vector4 Col);
	void settime(float t);
	Vector3 getVel();
	virtual ~Particle();
	
	// Clears accumulated force
	void clearForce();
	// Add force to apply in next integration only
	void addForce(const Vector3 f);
	Vector3 vel;
	float timer = 0;
	float time;
	unsigned _type;

protected:
	// Accumulated force
	Vector3 _force_accum;
	int masa;
	Vector3 acelera;
	Vector4 color;
	physx::PxTransform posicion;
	RenderItem* renderItem;// desregistrar el objeto
};

