#pragma once
#include <map>
#include "ForceGenerator.h"
using namespace std;
typedef pair <ForceGenerator*, Particle*> FRPair;

class ParticleForsceRegistry : public multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p);
	void deleteParticleRegistry(Particle* p);
private:

};