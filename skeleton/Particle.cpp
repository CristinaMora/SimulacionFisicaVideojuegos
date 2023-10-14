#include "Particle.h"

#include <iostream>
Particle* Particle::clone() {
	return new Particle(posicion.p, vel, acelera, masa, color,time, true);

}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 c,float t, bool render): posicion(Pos) {
	time = t;
	masa = mas;
	acelera = aceler;
	vel = Vel;
	color = c;
	if(render)	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(2)), &posicion,color);
}
bool  Particle::integrate(float t) {
	timer += t;
	vel += acelera * t;
	vel *= pow(damping, t);
	posicion.p = posicion.p + (vel * t);
	if (timer >= time) return true;
	else return false;
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
void Particle::settime(float t) {
	time = t;
}
void Particle::setCol(Vector4 col) {
	color = col;
	renderItem->color = col;
}
Vector3 Particle::getVel() {
	return vel;
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}
