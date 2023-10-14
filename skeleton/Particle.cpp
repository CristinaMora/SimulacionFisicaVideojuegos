#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 color): posicion(Pos) {
	masa = mas;
	acelera = aceler;
	vel = Vel;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
}
void Particle::integrate(float t) {
	timer += t;
	vel += acelera * t;
	vel *= pow(damping, t);
	posicion.p = posicion.p + (vel * t);
}
float Particle::gettimer() {
	return timer;
}
void Particle::setPos(Vector3 Pos) {
	posicion.p = Pos;
}
physx::PxTransform Particle::getPos() {
	return posicion;
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}
