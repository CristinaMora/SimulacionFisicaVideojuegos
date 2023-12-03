#pragma once
#include <map>
#include "ForceGenerator.h"
using namespace std;
typedef pair <ForceGenerator*, RigidBodyWithTime> SolidFR;
class SolidForceRegistry: public multimap<ForceGenerator*, RigidBodyWithTime> {
public:
	void updateForces(double duration);
	void addRegistry(ForceGenerator* fg, RigidBodyWithTime p);
	void deleteParticleRegistry(RigidBodyWithTime p);
};
