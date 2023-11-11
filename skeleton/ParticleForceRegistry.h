#pragma once
#include <map>
#include "ForceGenerator.h"
using namespace std;
typedef pair <ForceGenerator*, Particle*> FRPair;

class ParticleForsceRegistry : public multimap<ForceGenerator*, Particle*> {
public:
	inline void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}
	void addRegistry(ForceGenerator* fg, Particle* p) { //registra una particula
		this->insert(FRPair(fg, p));
	}
	void deleteParticleRegistry(Particle* p) {//borra una particula
		auto it = begin();
		while (it!=end())
		{
			if (it->second != p) ++it;
			else it = this->erase(it);
		}
	}
private:

};