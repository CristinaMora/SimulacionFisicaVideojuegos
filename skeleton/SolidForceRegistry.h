#pragma once
#include <map>
#include "ForceGenerator.h"
#include "RigidBody.h"
using namespace std;
typedef pair <ForceGenerator*, RigidBody> SolidFR;
class SolidForceRegistry: public multimap<ForceGenerator*, RigidBody> {
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, RigidBody p);
	void deleteParticleRegistry(RigidBody p);
};
