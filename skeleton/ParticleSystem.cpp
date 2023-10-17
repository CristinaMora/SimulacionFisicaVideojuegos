#include "ParticleSystem.h"
	
	ParticleSystem::ParticleSystem(const Vector3& g) {
		// Creates a void system with a det. gravity
		_gravity = g;
		_firework_generator = new GaussianParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
	};

	//destructora de la clase
	ParticleSystem::~ParticleSystem() {
	};

	// Integrates the particles and checks for its lifetime, etc!
	void ParticleSystem::update(double t){
		
		////creamos las nuevas particulas
		//list<ParticleGenerator*>::iterator x = _particle_generators.begin();
		//
		//	while (x != _particle_generators.end()) {
		//		auto aux = x;
		//		++aux;
		//		auto lista = (*x)->generateParticles();
		//		for (auto p : lista) _particles.push_back(p);
		//		_particle_generators.pop_back();
		//		x = aux;
		//	}
		
		//actualiza las particulas y las elimina en caso de que esten muertas
		list<Particle*>::iterator e = _particles.begin();
		while (e != _particles.end()) {
			auto aux = e;
			++aux;
			if ((*e)->integrate(t)){
				onParticleDeath(*e);
			}
			e = aux;
		}

	};
	// Method to generate a Firework with the appropiate type
	void ParticleSystem::generateFirework(){
		_part = new Firework(GetCamera()->getEye() - Vector3(30, 0, 40), GetCamera()->getDir() * 30, Vector3(0, -3.8, 0), 2, 3, Vector4{ 150 , 0, 0, 1 });
		_particles.push_back(_part);
		_part->addGenerator(_firework_generator);

	};
	// Gets a particle generator with name
	ParticleGenerator* ParticleSystem::getParticleGenerator(const string& n){
		
		return nullptr;
	};


	//! This is used currently in the Fireworks to spread more Fireworks!
	void ParticleSystem::onParticleDeath(Particle* p){
		
		if (p->_type == 0) {
			auto v = static_cast<Firework*>(p);
			if (v!= nullptr) {
				auto lista = v->explode();


				for (auto a : lista) _particles.push_back(a);
			}


		}
		_particles.remove(p);
		delete p;

	};
	void ParticleSystem::createFireworkSystem() {

	};
