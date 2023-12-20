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
	gravityForceGen = new GravityForceGenerator({ 0,0,72 });
	gravityForceGenContra = new GravityForceGenerator({0,0,2000});
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

Pala* RBManager::addPalas(bool l, Vector3 transform, const char* name)
{
	Pala* solid = new Pala();
	PxRigidDynamic* new_solid;
	//MATERIAL
	//POSICION
	new_solid = _gPhysics->createRigidDynamic(PxTransform(transform));
	//VELOCIDAD
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	//FORMA
	Vector3 dimension = { 27,20,5 };
		solid->shape = CreateShape(PxBoxGeometry(dimension.x, dimension.y, dimension.z));
	
	new_solid->attachShape(*solid->shape);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.5);
	//RENDERITEM
	solid->item = new RenderItem(solid->shape, new_solid, { 0.565, 1, 0.514,1 });
	_gScene->addActor(*new_solid);
	//TIEMPOS Y REGISTROS
	solid->body = new_solid;
	solid->tolive = 2147483647;
	new_solid->setName(name);
	solid->iniPos = new_solid->getGlobalPose().p;
	solid->left = l;
	solid->body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	
	return solid;

}
RigidBody RBManager::addDynamicObject(float Cestatico,float Cdinamico,float Elastico, PxVec3 inertiaT, Vector3 dimension,
	Vector4 color, Vector3 transform, Vector3 velocity,Vector3 angularvelocity, float density, int timetoleave, bool ball, const char* name)
{
		PxRigidDynamic* new_solid;
		//RigidBody solid;
		//MATERIAL
		PxMaterial* gMaterial = _gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);
		//POSICION

		new_solid = _gPhysics->createRigidDynamic(PxTransform(transform));
		//VELOCIDAD
		new_solid->setLinearVelocity(velocity);
		new_solid->setAngularVelocity(angularvelocity);
		PxShape* shape;
		//FORMA
		if (ball) {
			shape = CreateShape(PxSphereGeometry(dimension.x), gMaterial);
		}
		else {
			shape = CreateShape(PxBoxGeometry(dimension.x, dimension.y, dimension.z), gMaterial);
		}
		new_solid->attachShape(*shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, density);
		//new_solid->setMassSpaceInertiaTensor(inertiaT);
		//RENDERITEM
		RenderItem* item = new RenderItem(shape, new_solid, color);
		_gScene->addActor(*new_solid);
		//TIEMPOS Y REGISTROS
		RigidBody* solid = new RigidBody(new_solid, item, shape);
		solid->tolive = timetoleave;
		new_solid->setName(name);
		if (name == "pelota") {
			_sFR->addRegistry(gravityForceGen, *solid);
		}
		else if (name == "muelle") {

			new_solid->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			new_solid->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z );
		}
		new_solid->userData =solid;
		_objects.push_back(*solid);
		return *solid;

}
StaticRigidBody RBManager::addStaticObject(Vector3 dimension, Vector4 color, Vector3 transform, PxQuat rotate, bool ball, const char* name) {
	
	PxRigidStatic* suelo;
	PxTransform trans = PxTransform(transform);
	trans.q = rotate;
	suelo = _gPhysics->createRigidStatic(trans);
	//MATERIAL
	PxMaterial* gMaterial = _gPhysics->createMaterial(0.1f, 0.1f, 0.7f);
	PxShape* shape;
	if (ball) { //si es un circulo
		shape = CreateShape(PxSphereGeometry(dimension.x), gMaterial);
	}
	else { //si es un cuadrado 
		shape = CreateShape(PxBoxGeometry(dimension), gMaterial);
	}
	if (name == "trigger" || name == "triggerfinal" || name == "triggerregreso") {
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	}
	suelo->setName(name);
	suelo->attachShape(*shape);
	_gScene->addActor(*suelo);
	RenderItem* item;
	if (name == "tapa") {
		item = nullptr;
	}else 
	item =  new RenderItem(shape, suelo, color);
	StaticRigidBody* solid = new StaticRigidBody(suelo, item, shape, color);
	suelo->userData = solid;
	_statics.push_back(*solid);
	return *solid;
}
void RBManager::createscene() {
	//bordes
	addStaticObject(Vector3{ 150, 20, 2 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 0,3,300 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 150, 20, 2 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 0,3,-300 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 2, 20, 300 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -150,3,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 2, 20, 300 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 150,3,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	//el suelo
	addStaticObject(Vector3{ 150, 2, 300 }, Vector4{ 0.945, 0.71,1,1 }, Vector3{ 0,0,0 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 150, 2, 300 }, Vector4{ 0.945, 0.71,1,0 }, Vector3{ 0,13.999999,0 }, PxQuat(0, PxVec3(0, 1, 0)), false, "tapa");
	
	//esquina de abajo a la derecha
	addStaticObject(Vector3{ 3.04, 20, 42.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 96.96,1.5,267.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 70.96,1.5,230 }, PxQuat((-55.0f * PxPi / 180.0f), PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 45.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 97.96,1.5,168 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 256.5 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 125.96,1.5,41.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 55.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 20.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 37,1.5,205 }, PxQuat(PxPi / 2.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 38.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 35.96,1.5,173 }, PxQuat(-PxPi / 6.0f, PxVec3(0, 1, 0)));

	//abajo a la izquierda
	addStaticObject(Vector3{ 3.04, 20, 42.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -119.96,1.5,267.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -90.96,1.5,230 }, PxQuat((55.0f * PxPi / 180.0f), PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 45.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -120.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 34.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -75.96,1.5,173 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 20.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{-57,1.5,205 }, PxQuat(PxPi / 2.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 38.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -55.96,1.5,173 }, PxQuat(PxPi / 6.0f, PxVec3(0, 1, 0)));

	//arriba a la izquierda
	addStaticObject(Vector3{ 3.04, 21, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -126.96,1.5,-277.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -56.96,1.5,-277.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -35.4,1.5,-277.6 }, PxQuat(0, PxVec3(0, 1, 0)));

	//arriba derecha
	addStaticObject(Vector3{ 3.04, 21, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 129.96,1.5,-277.6 }, PxQuat((35.0f * PxPi / 180.0f), PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 33.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 100.96,1.5,-237.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 70.96,1.5,-257.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 15.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{-25,1.5,-257.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 10,1.5,-257.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 10.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 40,1.5,-257.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	
	addStaticObject(Vector3{ 3.04, 21, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 107.0,1.5,90.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 91.0,1.5,53.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 110.0,1.5,15.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 23.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 80.0,1.5,-15.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 77.43 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 95.0,1.5,-110.6 }, PxQuat(0, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 21, 16.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 85.0,1.5,-195.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));

	
	addStaticObject(Vector3{ 3.04, 20, 36.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -125.0,5,95.6 }, PxQuat(-PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 36.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -125.0,5,-50.6 }, PxQuat(PxPi / 4.0f, PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 25.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ 70.0,5,-226.6 }, PxQuat((10.0f * PxPi / 180.0f), PxVec3(0, 1, 0)));
	addStaticObject(Vector3{ 3.04, 20, 49.0 }, Vector4{ 0.18, 0.184, 0.851,1 }, Vector3{ -100.0,5,23.6 }, PxQuat(0, PxVec3(0, 1, 0)));


	
	
	//triggers
	addStaticObject(Vector3{ 6, 0, 0 }, Vector4{ 0.859, 0.439, 0,1 }, Vector3{ 105.0,3,-205.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "triggerregreso");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 55.0,3,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 25.0,3,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ -5,3,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ 85,3,5.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "trigger");
	addStaticObject(Vector3{ 3, 0, 0 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ -85,3,-20 }, PxQuat(0, PxVec3(0, 1, 0)), true, "trigger");
	addStaticObject(Vector3{ 3, 0, 0}, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ -100,3,-49 }, PxQuat(0, PxVec3(0, 1, 0)), true,"trigger");

	//rebotes
	addStaticObject(Vector3{ 10, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ -90.0,3,-255.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "rebote");
	addStaticObject(Vector3{ 10, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ 50.0,3,-185.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "rebote");
	addStaticObject(Vector3{ 10, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ 0.0,3,-155.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "rebote");
	addStaticObject(Vector3{ 10, 0, 0 }, Vector4{ 0, 0.988, 0.714 ,1 }, Vector3{ 30.0,3,-100.6 }, PxQuat(0, PxVec3(0, 1, 0)), true, "rebote");


	//mapa de arriba
	//las palas color = 0.565, 1, 0.514,1
	palaI = addPalas(true, { 20.96,2,257.6 }, "palaI");
	palaD = addPalas(false, { -45.96,2,257.6 },"palaD");

	//la pelota
	//bola= addDynamicObject(0.1f, 0.1f, 0.9f, { 0,0,0 }, { 5,0,0 }, { 0, 0, 0,0.25 }, { 45.0,4,-275.6 }, { 0,0,0 }, { 0,0,0 }, 0.5f, 2147483647, true, "pelota");
	
	//bola= addDynamicObject(0.1f, 0.1f, 0.8f, { 0,0,0 }, { 5,0,0 }, { 0, 0, 0,1 }, { 136.96,9,217.6 }, { 0,0,0 }, { 0,0,0 }, 30.0f, 2147483647, true, "pelota");
	bola= addDynamicObject(0.1f, 0.1f, 0.8f, { 0,0,0 }, { 5,0,0 }, { 0, 0, 0,1 }, { 0,9,257.6 }, { 0,0,0 }, { 0,0,0 }, 5.0f, 2147483647, true, "pelota");
	
	
	//muelle
	 muelle  = addDynamicObject(0.5f, 0.5f, 0.01f, { 0,0.1,0 }, { 8,4,3 }, { 0.18, 0.184, 0.851,1 }, { 143.5,10,255.6 }, { 0,0,0 }, { 0,0,0 }, 70000, 2147483647, false, "muelle");
	anchoredForceGen = new AnchoredSpringFG(6000000000, 40, { 138.5,10,295.6 }, _gPhysics, _gScene);
	//_sFR->addRegistry(anchoredForceGen, muelle);
	//_sFR->addRegistry(gravityForceGenContra, muelle);
	
	//triger final que termina la partida
	addStaticObject(Vector3{ 80, 14, 5 }, Vector4{ 0.98, 0.084, 0.051,1 }, Vector3{ -15,15,295.6 }, PxQuat(0, PxVec3(0, 1, 0)), false, "triggerfinal");

}
void RBManager::update(double t)
{
	_sFR->updateForces(t);
	if (fin) {
		for (auto it = _objects.begin(); it != _objects.end(); ) {
			
			_sFR->deleteParticleRegistry(*(it));
			_gScene->removeActor(*(it->body));
			(it->body)->detachShape(*(it->shape));
			(it->item)->release();
			(it->body)->release();
			it = _objects.erase(it);
			
		}
	}
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
	palaI->Update(t);
	palaD->Update(t);
}
void RBManager::keypress(unsigned char key)
{
	switch (toupper(key))
	{
		//INPUT
	case ' ':
		if (tenso && !fin) {
			tenso = false;
			muelle.body->clearForce();
			_sFR->deleteParticleRegistry(muelle);
			_sFR->addRegistry(anchoredForceGen, muelle);

		}
		else if(!fin) {
			_sFR->addRegistry(gravityForceGenContra, muelle);
			
			tenso = true;
		}
		//press enter to start
		break;
	
	default:
		break;
	}
}
void RBManager::createsplosion(RigidBody p1, Vector3 pos) {
	ExplosionForceGenerator* expl = new ExplosionForceGenerator(900000, 0.0000001,pos );
	_sFR->addRegistry(expl, p1);
}