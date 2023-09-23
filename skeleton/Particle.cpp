#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pose.p = Pos;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &pose,Vector4{20,20,20,1});
	RegisterRenderItem(renderItem);
}