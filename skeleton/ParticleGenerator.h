#pragma once
#include "Particle.h"
#include <list>
using namespace std;
class ParticleGenerator
{
public:
	
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p);
	inline void setMeanVelocity(const Vector3& v);
	inline Vector3 getMeanVelocity()const ;
	inline void setMeanDuration(double new_duration);
	inline void setParticle(Particle* p, bool modify_pos_vel = true);
	inline void setNParticles(int n_p);
protected:
		int _n_particles = 3; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
		double _generation_prob = 0.2; // IF 1.0 --> always produces  particles
		Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!
		Vector3 _origin, _mean_velocity;
		mt19937 _mt; //es como el random
		uniform_real_distribution<double> _u{ 0,1 };
		string _name;

};

