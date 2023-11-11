#include "Particle.h"

#include <iostream>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 c,float t , float radio, int type): posicion(Pos) {
	_type=type;
	time = t;
	masa = mas;
	acelera = aceler;
	vel = Vel;
	color = c;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radio)), &posicion,color);
}
bool  Particle::integrate(float t) {

	// Get the accel considering the force accum
	Vector3 resulting_accel = _force_accum * (1/masa);
	vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
	vel *= pow(damping, t); // Exercise 1.3 --> add damping
	posicion.p += vel * t;
	//_remaining_time -= delta_t;
	// Clear accum
	clearForce();


	//vel += acelera * t;
	//vel *= pow(damping, t);
	//posicion.p = posicion.p + (vel * t);
	timer += t;
	if (timer >= time) return true;
	else return false;
}
bool Particle::gettimer() {
	if (timer >= time) return false;
	else return true;
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
 void Particle::addForce(const Vector3 f) {
	_force_accum += f;
}
inline void Particle::clearForce() {
	_force_accum *= 0.0;
}

