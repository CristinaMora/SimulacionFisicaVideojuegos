#include "SolidForceRegistry.h"

void SolidForceRegistry::updateForces(double duration) {
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second.body, duration);
	}
}
void SolidForceRegistry::addRegistry(ForceGenerator* fg, RigidBodyWithTime p) { //registra una particula

	insert(SolidFR(fg, p));
}
void SolidForceRegistry::deleteParticleRegistry(RigidBodyWithTime p) {//borra una particula
	auto it = begin();
	while (it != end())
	{
		if (it->second.body != p.body){
			++it;
		}
		else it = this->erase(it);
	}
}