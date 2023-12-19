#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <iostream>
#include <list>
#include "RBManager.h"
#include "ParticleSystem.h"
#include <PxSimulationEventCallback.h>


std::string display_text = "Cristina Mora Velasco";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RBManager* _RBManager = nullptr;
ParticleSystem* _particleSystem = nullptr;
using namespace std;
int Puntos = 0;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	//INICIALIZACION DE LOS OBJETOS
	


	_particleSystem = new ParticleSystem();
	//_particleSystem->createscene(gScene,gPhysics );
	_RBManager = new RBManager(gPhysics, gScene);
	_RBManager->createscene();

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);

	//ACTUALIZACION DE LOS OBJETOS
	if (_particleSystem != nullptr)_particleSystem->update(t);
	if (_RBManager != nullptr)_RBManager->update(t);
	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	delete (_particleSystem);
	delete (_RBManager);
	//DESTRUCTORAS
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	_RBManager->keypress( key);
}

void onTriggere(physx::PxTriggerPair* pairs) {
	physx::PxActor* actor1 = static_cast<physx::PxActor*>(pairs->triggerActor);
	StaticRigidBody* p1 = static_cast<StaticRigidBody*>(actor1->userData);
	if (p1->body->getName()=="triggerfinal" ) {
		//se acaba la partida
		physx::PxActor* actor2 = static_cast<physx::PxActor*>(pairs->otherActor);
		RigidBody* p2 = static_cast<RigidBody*>(actor2->userData);
		const string a = actor2->getName();
		if (a == "pelota") {

			// Establece la nueva posición y mantiene la orientación actual
			PxTransform newTransform({ 105.0,3,-205.6 }, p2->body->getGlobalPose().q);

			// Aplica la nueva transformación al cuerpo
			p2->body->setGlobalPose(newTransform);
		}

	}
	else {
		if (p1->color == Vector4{ 0.98, 0.084, 0.051,1 }) {
			p1->color = Vector4{ 0.969, 0.965, 0.071,1 };
			p1->item->color = Vector4{ 0.969, 0.965, 0.071,1 };

		}
		else {
			p1->color = Vector4{ 0.98, 0.084, 0.051,1 };
			p1->item->color = Vector4{ 0.98, 0.084, 0.051,1 };
		}
	}
	
	cout << (Puntos += 100);
}
void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
		const string a = actor1->getName();
		const string b = actor2->getName();
		/*if (a == "trigger" && b=="pelota") {
			PX_UNUSED(actor1);
			PX_UNUSED(actor2);
			StaticRigidBody* p1 = static_cast<StaticRigidBody*>(actor1->userData);
			if (p1->color == Vector4{ 0.98, 0.084, 0.051,1 }) {
				p1->color = Vector4{ 0.969, 0.965, 0.071,1 };
				p1->item->color = Vector4{ 0.969, 0.965, 0.071,1 };
				
			}
			else {
				p1->color = Vector4{ 0.98, 0.084, 0.051,1 };
				p1->item->color = Vector4{ 0.98, 0.084, 0.051,1 };
			}
		}
		else if (b == "trigger" && a == "pelota") {
			PX_UNUSED(actor1);
			PX_UNUSED(actor2);
			StaticRigidBody* p1 = static_cast<StaticRigidBody*>(actor2->userData);
			if (p1->color == Vector4{ 0.98, 0.084, 0.051,1 }) {
				p1->color = Vector4{ 0.969, 0.965, 0.071,1 };
				p1->item->color = Vector4{ 0.969, 0.965, 0.071,1 };

			}
			else {
				p1->color = Vector4{ 0.98, 0.084, 0.051,1 };
				p1->item->color = Vector4{ 0.98, 0.084, 0.051,1 };
			}
		}*/
		PX_UNUSED(actor1);
		PX_UNUSED(actor2);
		
		
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}