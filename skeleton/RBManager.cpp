#include "RBManager.h"
RBManager::RBManager(PxPhysics* gPhysics, PxScene* gScene)
{
	//CREAMOS LA FISICA NECESARIA
	_gPhysics = gPhysics;
	_gScene = gScene;
	num = 30;
	//CREAMOS EL GENERADOR DE PARTICULAS
	_generator = new UniformParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 }, gPhysics, gScene);
	//GENERADOR DE FUERZAS
	windForceGen = new WindForceGenerator({ 0,0,6000.0f }, { 0, 0, -100 }, { 100, 100, 50 }, 1.0f, 0);
	//REGISTRO DE SOLIDO-FUERZA
	_sFR = new SolidForceRegistry();
	
}
RBManager::~RBManager() {
	
	for (auto& obj : _objects) {
		_gScene->removeActor(*(obj.body));
	}
	delete _generator;
	delete windForceGen;
	delete _sFR;
}
void RBManager::addDynamicObject()
{
		RigidBodyWithTime solid;
		PxRigidDynamic* new_solid;
		//POSICION
		new_solid = _gPhysics->createRigidDynamic(PxTransform({ -70,200,-70 }));
		new_solid->setLinearVelocity({ 0,-100,0 });
		new_solid->setAngularVelocity({ 0, 0, 0 });
		solid.shape = CreateShape(PxBoxGeometry(5, 5, 5));
		new_solid->attachShape(*solid.shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
		solid.item = new RenderItem(solid.shape, new_solid, { 0.5, 0.5, 0.5, 1 });
		_gScene->addActor(*new_solid);
		solid.body = new_solid;
		solid.tolive = 3;
		_sFR->addRegistry(windForceGen, solid);
		_objects.push_back(solid);
	
}
void RBManager::update(double t)
{
	//añadimos las partículas
	if (_objects.size() < num) {
		std::list<RigidBodyWithTime> lista = _generator->generateSolidRigid();
		for (auto partic : lista) {
			_objects.push_back(partic);
			_sFR->addRegistry(windForceGen, partic);

		}
		//addDynamicObject();
	}
	//las actualizamos
	for (auto it = _objects.begin(); it != _objects.end(); ) {
		it->time += t;
		if (it->time >= it->tolive) {
			_sFR->deleteParticleRegistry(*(it));
			_gScene->removeActor(*(it->body));
			(it->body)->detachShape(*(it->shape));
			(it->item)->release();
			(it->body)->release();
			it = _objects.erase(it);
		}
		else {
			++it;
		}
	}
	_sFR->updateForces(t);

}