#pragma once
#include "Particle.h"
#include <list>
using namespace std;
class ParticleGenerator
{
public:
	
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->timer = new_duration;
	}
	inline void setParticle(Particle* p, bool modify_pos_vel) {
		delete _model_particle;
		//_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPos().p;
			_mean_velocity = p->vel;
		}
		_model_particle->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNParticles(int n_p) { _n_particles = n_p; }

protected:
		int _n_particles = 4; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
		double _generation_prob = 0.2; // IF 1.0 --> always produces  particles
		Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!
		Vector3 _origin, _mean_velocity;
		mt19937 _mt; //es como el random
		uniform_real_distribution<double> _u{ 0,1 };
		string _name;

};

