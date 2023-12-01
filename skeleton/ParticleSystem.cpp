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
		whirlwindfChange_Force_Generator = new whirlwind({0.7f,0.03f,0.03f }, 2.0f,{10,0,0}, { 10,5,5 });
		listOfForceGenerators.push_back(whirlwindfChange_Force_Generator);
		_explosion_force_generator = new ExplosionForceGenerator(40000,300, {0,20,0},1000,100);
		listOfForceGenerators.push_back(_explosion_force_generator);


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
			delete whirlwindfChange_Force_Generator;
			delete _explosion_force_generator;
		
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

				if ((*e)->_type >= 1) {

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
			case 4: //tornado
				_pFR->addRegistry(whirlwindfChange_Force_Generator, p);
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
	void ParticleSystem::generateSpringDemo() {
		//creamos dos particulas
		
		p1 = new Particle({ 350,10,80 }, { 0,0,0 }, { 0,0,0 }, 2.0f, { 0.631, 0.196, 0.494, 1 }, 600, 4, 0);
		 p2 = new Particle({ 350,10,130 }, { 0,0,0 }, { 0,0,0 }, 2.0f,{ 0.631, 0.196, 0.494, 1 },600,4,0);
		//dos generadores
		SpringForceGenerator* f1 = new SpringForceGenerator(1, 30, p2);
		SpringForceGenerator* f2 = new SpringForceGenerator(1, 30, p1);
		//añades las dos conexiones
		_pFR->addRegistry(f1, p1);
		_pFR->addRegistry(f2, p2);
		listOfForceGenerators.push_back(f1);
		listOfForceGenerators.push_back(f2);
		_particles.push_back(p1);
		_particles.push_back(p2);

		

		 p3 = new Particle({ 450,40,60 }, { 0,0,0 }, { 0,0,0 }, 2.0f, { 0.631, 0.196, 0.494, 1 },600, 2, 0);
		f3 = new AnchoredSpringFG(k, 8, { 450,60, 60});
		_pFR->addRegistry(f3, p3);
		listOfForceGenerators.push_back(f3);
		_particles.push_back(p3);
		_pFR->addRegistry(_gravity_force_generator, p3);


	}
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

	void ParticleSystem::slinky() {
		float y = 100.0f;
		Particle* p = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 60.0f, { 0.969, 0.373, 0.792, 1 }, 15, 3, 0);
		y -= 10;
		Particle* p2 = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 20.0f, { 0.851, 0.325, 0.694, 1 }, 15, 3, 0);
		y -= 10;
		Particle* p3 = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 20.0f, { 0.69, 0.263, 0.561, 1 }, 15, 3, 0);
		y -= 10;
		Particle* p4 = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 20.0f, { 0.549, 0.208, 0.447, 1}, 15, 3, 0);
		y -= 10;
		Particle* p5 = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 20.0f, { 0.412, 0.153, 0.333, 1}, 15, 3, 0);
		y -= 10;
		Particle* p6 = new Particle({ 400,y,0 }, { 0,0,0 }, { 0,0,0 }, 20.0f, { 0.239, 0.09, 0.196, 1}, 15, 3, 0);
		_particles.push_back(p);
		_particles.push_back(p2);
		_particles.push_back(p3);
		_particles.push_back(p4);
		_particles.push_back(p5);
		_particles.push_back(p6);
		SpringForceGenerator* f = new SpringForceGenerator(100, 1, p);
		SpringForceGenerator* f1 = new SpringForceGenerator(100, 1, p2);
		SpringForceGenerator* f2 = new SpringForceGenerator(100, 1, p3);
		SpringForceGenerator* f3 = new SpringForceGenerator(100, 1, p4);
		SpringForceGenerator* f4 = new SpringForceGenerator(100, 1, p5);
		SpringForceGenerator* f5 = new SpringForceGenerator(100, 1, p6);
		_pFR->addRegistry(f, p2);
		_pFR->addRegistry(f1, p);
		_pFR->addRegistry(f1, p3);
		_pFR->addRegistry(f2, p2);
		_pFR->addRegistry(f2, p4);
		_pFR->addRegistry(f3, p3);
		_pFR->addRegistry(f3, p5);
		_pFR->addRegistry(f4, p4);
		_pFR->addRegistry(f4, p6);
		_pFR->addRegistry(f5, p5);/*
		_pFR->addRegistry(_gravity_force_generator, p2);
		_pFR->addRegistry(_gravity_force_generator, p3);
		_pFR->addRegistry(_gravity_force_generator, p4);
		_pFR->addRegistry(_gravity_force_generator, p5);
		_pFR->addRegistry(_gravity_force_generator, p6);*/
	}
	void ParticleSystem::buoyancy() {

		//	//particula en forma cuadrada
		Particle* parti = new Particle({ 1, 0.984, 0.678,1.0 }, { 5.0f, 5.0f, 5.0f }, { 450,15,80 }, 5.0f, 600.0f, 0);
		_particles.push_back(parti);
		_pFR->addRegistry(_gravity_force_generator, parti);
		BuoyancyForceGenerator* f = new BuoyancyForceGenerator(5, 10, 30, { 450,0,80 });
		_pFR->addRegistry(f, parti);
	}



