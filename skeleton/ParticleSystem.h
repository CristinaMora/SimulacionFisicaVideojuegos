#pragma once
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
class ParticleSystem
{
	public:
		// Creates a void system with a det. gravity
		ParticleSystem(const Vector3& g = { 0.0f, -3.8, 0.0f});
		virtual ~ParticleSystem();
		// Integrates the particles and checks for its lifetime, etc!
		void update(double t);
		// Method to generate a Firework with the appropiate type
		void generateFirework(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acel, int masa, float t, Vector4 c, int radio);
		void generateParticleGenerator();
		// Gets a particle generator with name...
		ParticleGenerator* getParticleGenerator(const string& n);
	protected:
		Firework* _part = nullptr;
		list <Particle*> _particles;
		list<Firework*> _firework_pool;
		list<ForceGenerator*> listOfForceGenerators;
		list <ParticleGenerator*> _particle_generators; 
		ParticleGenerator* _firework_generator; 
		Vector3 _gravity;
		void onParticleDeath(Particle * p);
		void createFireworkSystem();
		ParticleDragGenerator* _particle_drag_generator;
		GravityForceGenerator* _gravity_force_generator;
};