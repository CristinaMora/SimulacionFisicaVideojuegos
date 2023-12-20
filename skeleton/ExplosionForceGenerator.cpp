#include "ExplosionForceGenerator.h"
#include <numbers>

bool ExplosionForceGenerator::updateForce(PxRigidBody* p, double t)
{

		Vector3 aux = p->getGlobalPose().p - position;
		double r = sqrt((aux.x * aux.x + aux.y * aux.y + aux.z * aux.z));
		Vector3 f = (k / (r * r)) * aux * exp(-t / timeConstant);
		p->addForce(f);
		timetodelete += t;
		if (timetodelete >= 5) {
			//borrar la fuerza
			return false;
		}
		return true;

}
void ExplosionForceGenerator::updateForce(Particle* particle, double t) {}

