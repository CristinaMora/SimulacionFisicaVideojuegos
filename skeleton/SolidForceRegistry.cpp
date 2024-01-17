#include "SolidForceRegistry.h"

void SolidForceRegistry::updateForces(double duration) {

	auto it = begin();
	while (it != end()) {
		bool todelete = it->first->updateForce(it->second.body, duration);
		if (!todelete) {
			auto it2 = it;
			it2++;
			erase(it);			
			it = it2;
		}
		else {
			++it; // Solo incrementa el iterador si no se elimina el elemento
		}
	}

}
void SolidForceRegistry::addRegistry(ForceGenerator* fg, RigidBody p) { //registra una particula

	insert(SolidFR(fg, p));
}
void SolidForceRegistry::deleteParticleRegistry(RigidBody p) {//borra una particula
	auto it = begin();
	while (it != end())
	{
		if (it->second.body != p.body){
			++it;
		}
		else it = this->erase(it);
	}
}