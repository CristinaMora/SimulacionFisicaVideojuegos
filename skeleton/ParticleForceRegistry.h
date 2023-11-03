#pragma once
#include <map>
#include "ForceGenerator.h"
using namespace std;
typedef pair <ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}
	void addRegistry(ForceGenerator* fg, Particle* p);
	void deleteParticleRegistry(Particle* p);
private:

};