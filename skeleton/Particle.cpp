#include "Particle.h"
Particle* Particle::clone() {
	return new Particle(posicion.p, vel, acelera, masa, color);

}
//crear una particula de 0
//Particle* Particle::clone() {
//	return new Particle(GetCamera()->getEye() - Vector3(30, 0, 40), GetCamera()->getDir() * 30, Vector3(0, -3.8, 0), 2, Vector4{ 150 , 0, 50, 1 });
//
//}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas, Vector4 c): posicion(Pos) {
	masa = mas;
	acelera = aceler;
	vel = Vel;
	color = c;
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
void Particle::setVel(Vector3 Vel) {
	vel = Vel;
}
Vector3 Particle::getVel() {
	return vel;
}
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}
