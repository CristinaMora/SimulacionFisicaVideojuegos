#include "RBManager.h"
RBManager::RBManager(PxPhysics* gPhysics, PxScene* gScene)
{
	//CREAMOS LA FISICA NECESARIA
	_gPhysics = gPhysics;
	_gScene = gScene;
	num = 0;
	//CREAMOS EL GENERADOR DE PARTICULAS
	_generator = new UniformParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 }, gPhysics, gScene);
	//GENERADOR DE FUERZAS
	windForceGen = new WindForceGenerator({ 0,0,6000.0f }, { 0, 0, -100 }, { 100, 100, 50 }, 1.0f, 0);
	gravityForceGen = new GravityForceGenerator({0,0,9.8});
	anchoredForceGen;
	//REGISTRO DE SOLIDO-FUERZA
	_sFR = new SolidForceRegistry();
	
}
RBManager::~RBManager() {
	
	for (auto& obj : _objects) {
		_gScene->removeActor(*(obj.body));
	}
	delete _generator;
	delete windForceGen;
	delete gravityForceGen;
	delete _sFR;
}
RigidBody RBManager::addDynamicObject(float Cestatico,float Cdinamico,float Elastico, PxVec3 inertiaT, Vector3 dimension,
	Vector4 color, Vector3 transform, Vector3 velocity,Vector3 angularvelocity, float density, int timetoleave, bool ball, const char* name)
{
		RigidBody solid;
		PxRigidDynamic* new_solid;
		//MATERIAL
		PxMaterial* gMaterial = _gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
		//POSICION
		new_solid = _gPhysics->createRigidDynamic(PxTransform(transform));
		//VELOCIDAD
		new_solid->setLinearVelocity(velocity);
		new_solid->setAngularVelocity(angularvelocity);
		//FORMA
		if (ball) {
			solid.shape = CreateShape(PxSphereGeometry(dimension.x), gMaterial);
		}
		else {
			solid.shape = CreateShape(PxBoxGeometry(dimension.x, dimension.y, dimension.z), gMaterial);
		}
		new_solid->attachShape(*solid.shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, density);
		//new_solid->setMassSpaceInertiaTensor(inertiaT);
		//RENDERITEM
		solid.item = new RenderItem(solid.shape, new_solid, color);
		_gScene->addActor(*new_solid);
		//TIEMPOS Y REGISTROS
		solid.body = new_solid;
		solid.tolive = timetoleave;
		new_solid->setName(name);
		if (name == "pelota") {
			_sFR->addRegistry(gravityForceGen, solid);
		}
		if (name == "muelle") {
		}
		_objects.push_back(solid);
		return solid;

}
StaticRigidBody RBManager::addStaticObject(Vector3 dimension, Vector4 color, Vector3 transform, PxQuat rotate, bool ball, const char* name) {
	
	PxRigidStatic* suelo;
	PxTransform trans = PxTransform(transform);
	trans.q = rotate;
	suelo = _gPhysics->createRigidStatic(trans);
	//MATERIAL
	PxMaterial* gMaterial = _gPhysics->createMaterial(0.5f, 0.5f, 0.0f);
	PxShape* shape;
	if (ball) {
		shape = CreateShape(PxSphereGeometry(dimension.x), gMaterial);
	}
	else {
		shape = CreateShape(PxBoxGeometry(dimension), gMaterial);
	}
	if (name == "trigger") {
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	}
	suelo->setName(name);
	suelo->attachShape(*shape);
	_gScene->addActor(*suelo);
	RenderItem* item =  new RenderItem(shape, suelo, color);
	StaticRigidBody* solid = new StaticRigidBody(suelo, item, shape, color);
	suelo->userData = solid;
	_statics.push_back(*solid);
	return *solid;
}
void RBManager::createscene() {
	//bordes
	addStaticObject(Vector3{ 150, 5, 2 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 0,3,300 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 150, 5, 2 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 0,3,-300 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 2, 5, 300 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -150,3,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 2, 5, 300 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 150,3,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	//el suelo
	addStaticObject(Vector3{ 150, 2, 300 }, Vector4{ 0.945, 0.71,1,1 }, Vector3{ 0,0,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	
	//esquina de abajo a la derecha
	//addStaticObject(Vector3{ 13.04, 5, 32.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 136.96,1.5,267.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 42.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 96.96,1.5,267.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 70.96,1.5,230 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 95.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 246.5 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 125.96,1.5,30.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 55.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 20.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 37,1.5,205 }, PxQuat(PxPi / 2.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 38.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 35.96,1.5,173 }, PxQuat(-PxPi / 6.0f, PxVec3(0, 1, 0)));

	//abajo a la izquierda
	addStaticObject(Vector3{ 3.04, 5, 42.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -119.96,1.5,267.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -90.96,1.5,230 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -115.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -75.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 20.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{-57,1.5,205 }, PxQuat(PxPi / 2.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 38.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -55.96,1.5,173 }, PxQuat(PxPi / 6.0f, PxVec3(0, 1, 0)));

	//arriba a la izquierda
	addStaticObject(Vector3{ 3.04, 5, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -126.96,1.5,-277.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -56.96,1.5,-277.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -35.4,1.5,-277.6 }, PxQuat(0, PxVec3(0, 1, 0)));

	//arriba derecha
	addStaticObject(Vector3{ 3.04, 5, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 126.96,1.5,-277.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 100.96,1.5,-237.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 70.96,1.5,-257.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 15.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{-25,1.5,-257.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 10,1.5,-257.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 40,1.5,-257.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	
	addStaticObject(Vector3{ 3.04, 5, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 107.0,1.5,90.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 91.0,1.5,53.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 110.0,1.5,15.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 80.0,1.5,-15.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 77.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 95.0,1.5,-110.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 5, 16.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 85.0,1.5,-195.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));

	
	addStaticObject(Vector3{ 3.04, 10, 36.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -125.0,5,95.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 10, 36.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -125.0,5,-50.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 10, 49.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -100.0,5,23.6 }, PxQuat(0, PxVec3(0, 1, 0)));


	
	
	//triggers
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 105.0,1.5,-205.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 55.0,1.5,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 25.0,1.5,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ -5,1.5,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0}, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 85,1.5,5.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");

	//rebotes
	addStaticObject(Vector3{ 7, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ -90.0,1.5,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true);
	addStaticObject(Vector3{ 7, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ 70.0,1.5,-155.6 }, PxQuat(0, PxVec3(0, 1, 0)), true);
	addStaticObject(Vector3{ 7, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ -20.0,1.5,-135.6 }, PxQuat(0, PxVec3(0, 1, 0)), true);
	addStaticObject(Vector3{ 7, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ 30.0,1.5,-100.6 }, PxQuat(0, PxVec3(0, 1, 0)), true);

	//las palas color = 0.565, 1, 0.514,1
	
	addDynamicObject(0.5f, 0.5f, 0.6f, { 0,0,0 }, { 4,2,2 }, { 0.565, 1, 0.514,1 }, { -36.96,2,217.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, false, "pala1");
	addDynamicObject(0.5f, 0.5f, 0.6f, { 0,0,0 }, { 4,2,2 }, { 0.565, 1, 0.514,1 }, { -66.96,2,217.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, false, "pala2");

	//la pelota
	addDynamicObject(0.1f, 0.1f, 0.6f, { 0,0,0 }, { 5,0,0 }, { 0, 0, 0,0.25 }, { 55.0,4,-275.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, true, "pelota");
	//addDynamicObject(0.5f, 0.5f, 0.6f, { 0,0,0 }, { 5,0,0 }, { 0, 0, 0,1 }, { 136.96,9,217.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, true, "pelota");
	//muelle

	/*RigidBody muelle  = addDynamicObject(0.5f, 0.5f, 0.01f, { 0,0,0 }, { 1.04, 1, 2.43 }, { 0.18, 0.184, 0.851,1 }, { 136.96,27,267.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, false, "muelle");
	muelle.body->setMass(2);
	anchoredForceGen = new AnchoredSpringFG(1, 20, { 136.96,30,267.6 }, _gPhysics, _gScene);
	_sFR->addRegistry(anchoredForceGen, muelle);*/

}
void RBManager::update(double t)
{
	_sFR->updateForces(t);

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

}