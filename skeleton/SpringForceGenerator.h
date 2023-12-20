#pragma once
#include "ForceGenerator.h"
#include <PxPhysics.h>
class SpringForceGenerator: public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	SpringForceGenerator( double resting_length, PxRigidStatic* other, double k);
	virtual void updateForce(Particle* particle, double t);
	virtual bool updateForce(physx::PxRigidBody* solid, double t);
	~SpringForceGenerator();
	inline void setk(double k) { _k = k; };
	inline double getK() { return _k; }
protected:
	double _k; //coeficiente elastico
	double _resting_length;
	Particle* _other;
	physx::PxRigidStatic* _other2;
};

//DOS PARTICULAS UNIDAS POR MUELLES