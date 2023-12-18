#include "Particle.h"

//CONSTRUCTORAS
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 aceler,double mas,Vector4 c,float t, Vector3 tam, int type) : posicion(Pos) {
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

//METODO QUE SE UTILIZA PARA ACTUALIZAR LA PARTICULA Y QUE DEVUELVE SI SIGUE VIVA O NO
bool  Particle::integrate(float t) {

	//FORMULA DE EULER SEMI IMPLICITA
	Vector3 resulting_accel = acelera + _force_accum * (1/masa);
	vel += resulting_accel * t; 
	vel *= pow(damping, t); 
	posicion.p += vel * t;
	//RESETEAMOS LAS FUERZAS
	clearForce();

	//CALCULAMOS EL TIEMPO
	timer += t;
	//SI EL TIMER ES MAYOR QUE EL TIEMPO ENTONCESTIENE QUE MORIR
	if (timer >= time) return true;
	else return false;
}

//METODO PARA BORRAR Y AÑADIR FUERZAS
void Particle::addForce(const Vector3 f) {
	_force_accum += f;
}
inline void Particle::clearForce() {
	_force_accum *= 0.0;
}

//GETTER Y SETTER PARA LA POSICION
void Particle::setPos(Vector3 Pos) {
	posicion.p = Pos;
}
Vector3 Particle::getPos() {
	return posicion.p;
}
//GETTER Y SETTER PARA LA VELOCIDAD
void Particle::setVel(Vector3 Vel) {
	vel = Vel;
}
Vector3 Particle::getVel() {
	return vel;
}

//SETTER DEL TIEMPO Y BOOL DE VIDA
bool Particle::getAlive() {
	if (timer >= time) return false;
	else return true;
}
void Particle::settime(float t) {
	time = t;
}
//SETTER DEL COLOR
void Particle::setCol(Vector4 col) {
	color = col;
	renderItem->color = col;
}
double Particle::getMass() {
	return masa;
}
int Particle::getType() {
	return _type;
}
//DESTRUCTORA
Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}


