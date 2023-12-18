#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator {
public:
	GravityForceGenerator(const Vector3& g) { _gravity = g; };
	void updateForce(Particle* particle, double t) override;
	void updateForce(physx::PxRigidBody* solid, double duration) override;
	inline void setGravity(Vector3 g) { _gravity = g; }
	~GravityForceGenerator(){};
protected:
	Vector3 _gravity;
};
