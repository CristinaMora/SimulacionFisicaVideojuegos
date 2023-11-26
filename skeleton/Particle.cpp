#include "Particle.h"

#include <iostream>
Particle::Particle(Vector4 c, Vector3 tam, Vector3 Pos, double mas, float t, int type) : posicion(Pos) {
	_type = type;
	time = t;
	masa = mas;
	acelera = { 0,0,0 };
	vel = { 0,0,0 };
	color = c;
	_force_accum = { 0,0,0 };

	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(tam)), &posicion, color);
}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, double mas, Vector4 c,float t , float radio, int type): posicion(Pos) {
	_type=type;
	time = t;
	masa = mas;
	acelera = aceler;
	vel = Vel;
	color = c;
	_force_accum = { 0,0,0 };

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radio)), &posicion,color);
}
Particle::Particle(RenderItem* render, physx::PxTransform pos, Vector3 Vel, double mas, float t, int type){
	_type = type;
	time = t;
	masa = mas;
	acelera = {0,0,0};
	vel = Vel;
	_force_accum = { 0,0,0 };
	renderItem = render;
	posicion = pos;
}

bool  Particle::integrate(float t) {

	// Get the accel considering the force accum
	Vector3 resulting_accel = acelera + _force_accum * (1/masa);
	//euler
	// posicion.p =posicion.p+vel*t;
	// vel = vel+ resulting_accel*t;
	//euler semi- implicito
	vel += resulting_accel * t; 
	vel *= pow(damping, t); 
	posicion.p += vel * t;
	clearForce();

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

