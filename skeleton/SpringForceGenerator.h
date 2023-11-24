#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator: public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle, double t);
	~SpringForceGenerator();
	inline void setk(double k) { _k = k; };
	inline double getK() { return _k; }
protected:
	double _k; //coeficiente elastico
	double _resting_length;
	Particle* _other;
};

//DOS PARTICULAS UNIDAS POR MUELLES