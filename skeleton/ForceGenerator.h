#pragma once
#include <string>
#include "Particle.h"
using namespace std;
class ForceGenerator {
public:
	bool isOn = false;
	virtual void updateForce(Particle* particle, double duration) = 0;
	virtual void updateForce(physx::PxRigidBody* solid, double duration);
	std::string _name;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
	}
	virtual ~ForceGenerator() {}
};
