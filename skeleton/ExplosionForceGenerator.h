#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator : public ForceGenerator
{
public:

	ExplosionForceGenerator(double K, double constant, Vector3 pos) : k(K), timeConstant(constant), position(pos){}
	~ExplosionForceGenerator(){};
	void updateForce(Particle* particle, double t) override;
	bool updateForce(physx::PxRigidBody* solid, double duration) override;
	void setCoefficient(double K) { k = K; };

	void setConstant(double constant) { timeConstant = constant; };

	void setExplosion(double r) {};

protected:
	double timetodelete = 0;
	Vector3 position;
	double k;
	double timeConstant;
private:
};