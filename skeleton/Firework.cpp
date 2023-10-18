#include "Firework.h"
#include "ParticleGenerator.h"
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas,float t, Vector4 c, float radio, int type):Particle(Pos, Vel, aceler, mas, c, t, radio, type){
	
}

std::list<Particle*> Firework::explode() {
	_gens.front()->setOrigin(posicion.p);
	_gens.front()->setMeanVelocity(vel);
	return _gens.front()->generateParticles(_type);
}
void Firework::addGenerator(ParticleGenerator* p) {
	_gens.push_back(p);
}
Firework::~Firework() {
}