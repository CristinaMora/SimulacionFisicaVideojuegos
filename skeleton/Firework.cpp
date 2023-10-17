#include "Firework.h"
#include "ParticleGenerator.h"
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas,float t, Vector4 c):Particle(Pos, Vel, aceler, mas, c, t){
	_type = 0;
}

std::list<Particle*> Firework::explode() {
	auto c = _gens.front();
	c->setOrigin(posicion.p);
	c->setMeanVelocity(vel);
	return c->generateParticles();
}
void Firework::addGenerator(ParticleGenerator* p) {
	_gens.push_back(std::shared_ptr<ParticleGenerator>(p));
}