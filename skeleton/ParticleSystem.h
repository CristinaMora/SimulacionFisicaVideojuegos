#pragma once
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "whirlwind.h"
class ParticleSystem
{
	public:
		// Creates a void system with a det. gravity
		ParticleSystem(const Vector3& g = { 0.0f, -3.8, 0.0f});
		virtual ~ParticleSystem();
		// Integrates the particles and checks for its lifetime, etc!
		void update(double t);
		// Method to generate a Firework with the appropiate type
		void generateFirework(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acel, double masa, float t, Vector4 c, int radio);
		void generateParticleGenerator();
		void activeGrav() { _gravity_force_generator->isOn = true; }
		// Gets a particle generator with name...
		ParticleGenerator* getParticleGenerator(const string& n);
	protected:
		Firework* _part = nullptr;
		list <Particle*> _particles;
		list<Firework*> _firework_pool;
		list <ParticleGenerator*> _particle_generators; 
		ParticleGenerator* _firework_generator; 
		Vector3 _gravity;
		void onParticleDeath(Particle * p);
		void createFireworkSystem();

		//FUERZAS
		list<ForceGenerator*> listOfForceGenerators;
		ParticleForsceRegistry* _pFR;
		WindofChangeForceGenerator* _WindofChange_Force_Generator;
		whirlwind* whirlwindfChange_Force_Generator;
		GravityForceGenerator* _gravity_force_generator;
};