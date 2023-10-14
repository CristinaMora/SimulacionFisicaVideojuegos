#include "Particle.h"
Particle* Particle::clone() {
	return new Particle(posicion.p, vel, acelera, masa, color, true);

}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 c, bool render): posicion(Pos) {
	masa = mas;
	acelera = aceler;
	vel = Vel;
	color = c;
	if(render)	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
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
void Particle::setVel(Vector3 Vel) {
	vel = Vel;
}
Vector3 Particle::getVel() {
	return vel;
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}
