#pragma once
#include "ParticleDragGenerator.h"
class WindForceGenerator : public ParticleDragGenerator {
public:
	WindForceGenerator(Vector3 fuerzaViento, Vector3 origen, Vector3 tam, const float k1, const float k2);
	Vector3 f;
	virtual void updateForce(Particle* particle, double t) override;
	void updateForce(physx::PxRigidBody* solid, double duration) override;

protected:
	Vector3 porigen, size;
};