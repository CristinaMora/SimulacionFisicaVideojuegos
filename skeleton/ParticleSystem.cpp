#include "ParticleSystem.h"
	
	ParticleSystem::ParticleSystem() {
		_firework_generator = new UniformParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_firework_generator = new GaussianParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_pFR = new ParticleForsceRegistry();

		
		_gravity_force_generator = new GravityForceGenerator({0,-9.8f,0});
		listOfForceGenerators.push_back(_gravity_force_generator);
		_gravityMoon_force_generator = new GravityForceGenerator({ 0,-1.62f,0 });
		listOfForceGenerators.push_back(_gravityMoon_force_generator);
		_Wind_Force_Generator = new WindForceGenerator({0,0,3.0f},{ 0, 0, -100 },{ 100, 100, 50 },1.0f , 0);
		listOfForceGenerators.push_back(_Wind_Force_Generator);
	};

	//destructora de la clase
	ParticleSystem::~ParticleSystem() {
		

			for (auto e : _particles)
			{
				delete e;
			}
			_particles.clear();
			for (auto e : _firework_pool) {
				delete e;
			}
			_firework_pool.clear();
			for (auto e : _particle_generators)
			{
				_particle_generators.pop_front();
			}
			delete _gravity_force_generator;
			delete _Wind_Force_Generator;
		
	};

	// Integrates the particles and checks for its lifetime, etc!
	void ParticleSystem::update(double t){
		
		_pFR->updateForces(t);
		//actualiza las particulas y las elimina en caso de que esten muertas
		
		//lista de generadores fuentes
		/*for (auto gen : _particle_generators) {
			std::list<Particle*> lista = gen->generateParticles();
			for (auto partic : lista) {
				_particles.push_back(partic);
			}
			
		}*/
		//lista de particulas, se actualizan, explotan...
		list<Particle*>::iterator e = _particles.begin();
		while (e != _particles.end()) {
			auto aux = e;
			++aux;

			if ((*e)->integrate(t)) {

				if ((*e)->getType() >= 1) {

					Firework* firework = static_cast<Firework*>(*e);
					std::list<Particle*> p = firework->explode();

					for (auto d : p) {
						_particles.push_back(d);
						_pFR->addRegistry(_gravity_force_generator, d);
					}
				}
				onParticleDeath(*e);
			}
			e = aux;
		
		}
		

	};
	// Method to generate a Firework with the appropiate type
	void ParticleSystem::generateFirework(unsigned firework_type, Vector3 pos,Vector3 vel, Vector3 acel, double masa,float t,Vector4 c, int radio){
		_part = new Firework(pos, vel, acel, masa, t, c, radio, firework_type);
		_particles.push_back(_part);
		if(firework_type!=4) _part->addGenerator(_particle_generators.back());
		else _part->addGenerator(_particle_generators.front());
		_pFR->addRegistry(_gravity_force_generator, _part);
		

	};
	void ParticleSystem::generateParticle(unsigned forcetype, Vector3 pos, Vector3 vel, Vector3 acel, double masa, float t, Vector4 c, int radio) {
		Particle* p = new Particle(pos, vel, acel, masa, c, t, radio, 0);
		_particles.push_back(p);
		switch (forcetype)
		{
			case 1: //gravedad
				_pFR->addRegistry(_gravity_force_generator, p);
				break;
			case 2: //gravedad luna
				_pFR->addRegistry(_gravityMoon_force_generator, p);
				break;
			case 3: //viento
				_pFR->addRegistry(_Wind_Force_Generator, p);
				break;
			default:
				break;
		}


	};


	//destructora de las particulas
	void ParticleSystem::onParticleDeath(Particle* particleaa){
		
		//se borran del multi map, de la lista y se llama a la destructora de la particula
		_pFR->deleteParticleRegistry(particleaa);
		_particles.remove(particleaa);
		 delete (particleaa);
		

	};
	void ParticleSystem::createscene(PxScene* gScene, PxPhysics* gPhysics) {

		suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
		shape = CreateShape(PxBoxGeometry(400, 0.2, 400));
		suelo->attachShape(*shape);
		gScene->addActor(*suelo);
		RenderItem* item;
		item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1 });

		//suelgo gris
		//base = new RenderItem(CreateShape(PxBoxGeometry(500, 1, 500)), new PxTransform(0, 0,0), { 0.51f, 0.486f, 0.455f,1.0f });
		
	
	};
	void ParticleSystem::Deleteforce() {
		cout << "se quita\n";
		_pFR->deleteParticleRegistry(p3);
		_pFR->addRegistry(f3, p3);
		_pFR->addRegistry(_gravity_force_generator, p3);
	}
	void ParticleSystem::addforce() {
		cout << "se añade\n";
		GravityForceGenerator* grav = new GravityForceGenerator({ 0,0,7.5 });
		listOfForceGenerators.push_back(grav);
		_pFR->addRegistry(grav, p3);

	}



