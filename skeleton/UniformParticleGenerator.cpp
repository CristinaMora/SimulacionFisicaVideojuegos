#include "UniformParticleGenerator.h"
#include "Firework.h"
#include <random>
//constructora
UniformParticleGenerator::UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
}
UniformParticleGenerator::UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, PxPhysics* gPhysics, PxScene* gScene) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
	_gScene = gScene;
	_gPhysics = gPhysics;
}
//destructora
UniformParticleGenerator::~UniformParticleGenerator() {}

list<Particle*> UniformParticleGenerator::generateParticles(int type) {
	switch (type)
	{
	case 4:
		return generatefirework1();
	default:
		break;
	}
    
}
std::list<Particle*>  UniformParticleGenerator::generatefirework1() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {
		// Genera posiciones y velocidades muestreadas de una distribución gaussiana
		Vector3 Vel =  Vector3(0, dis(_mt) * stdDevVel.y, 0);
		Vector3 Pos = _origin + Vector3(dis(_mt) * stdDevPos.x, dis(_mt) * stdDevPos.y, dis(_mt) * stdDevPos.z);
		float time = dis1(_mt);
		float radio = 0.6;
		Vector4 Col(0.655, 0.804, 0.91,1);
		particles.push_back(new Particle(Pos, Vel, Vector3(0, 0, 0), 0.2f, Col, time, radio, 0));
	}

	return particles;
};
std::list<RigidBody> UniformParticleGenerator::generateSolidRigid() {
	std::list<RigidBody> solidss;
	for (int i = 0; i < nsolid; i++) {
		RigidBody solid;
		PxRigidDynamic* new_solid;
		//POSICION
		Vector3 position = Vector3{ -70,200,-70 } + Vector3(dis(_mt) * stdDevPos.x, dis(_mt) * stdDevPos.y, dis(_mt) * stdDevPos.z);
		new_solid = _gPhysics->createRigidDynamic(PxTransform(position));
		new_solid->setLinearVelocity({ 0,-100* dis(_mt),0 });
		new_solid->setAngularVelocity({ 0, 0, 0 });
		solid.shape = CreateShape(PxBoxGeometry(5, 5, 5));
		new_solid->attachShape(*solid.shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
		solid.item = new RenderItem(solid.shape, new_solid, { 1, 0.5, 1, 1 });
		_gScene->addActor(*new_solid);
		solid.body = new_solid;
		solid.tolive = dis1(_mt);
		solidss.push_back(solid);
	}
	return solidss;
	
}