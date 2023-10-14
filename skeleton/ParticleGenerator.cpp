#include "ParticleGenerator.h"

inline void ParticleGenerator::setOrigin(const Vector3& p) { _origin = p; }
inline void ParticleGenerator::setMeanVelocity(const Vector3& v) {
	_mean_velocity= v;
}

inline Vector3 ParticleGenerator::getMeanVelocity() const {
	return _mean_velocity;
}
inline void ParticleGenerator::setMeanDuration(double new_duration) {
	_model_particle->timer = new_duration;
}
inline void ParticleGenerator::setParticle(Particle* p, bool modify_pos_vel) {
	delete _model_particle;
	_model_particle = p->clone();
	if (modify_pos_vel) {
		_origin = p->getPos().p;
		_mean_velocity = p->vel;
	}
	_model_particle->setPos({ -1000.0f, -1000.0f, -1000.0f });
}
inline void ParticleGenerator::setNParticles(int n_p) { _n_particles = n_p; }