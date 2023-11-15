#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSystem.h"
#include <iostream>
#include <list>
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
ParticleSystem*         psistem = nullptr;
ContactReportCallback gContactReportCallback;
using namespace std;

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
	//me creo un sistema de particulas que actualizara las particulas en todo momento
	psistem = new ParticleSystem();
	psistem->createscene();

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);
	if (psistem != nullptr)psistem->update(t);

	
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
	delete (psistem);
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	switch(toupper(key))
	{
	case 'P':
		psistem->boom();
		break;
	case 'I':
		psistem->generateFirework(2, GetCamera()->getEye() + Vector3(-90, -90, -90), Vector3(0, 1, 0) * 50, Vector3(0, 0, 0), 0.2f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
	break;
	case 'O':
		psistem->generateFirework(2, GetCamera()->getEye() + Vector3(-90, -90, -90), Vector3(0, 1, 0) * 50, Vector3(0, 0, 0), 0.2f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
		break;
	case 'U':
		psistem->generateParticle(3, { 0,18,0 }, Vector3(0, 0, 1) * (-80), Vector3(0, 0, 0), 0.5f, 100, Vector4{ 150 , 0, 50, 1 }, 10);
		break;
	case 'R':
		psistem->generateFirework(2, Vector3(0, 2, 200), Vector3(0, 1, 0) * 80, Vector3(0, 0, 0), 0.02f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
		break;
	case 'T':
		psistem->generateFirework(3, Vector3(0, 2, 100), Vector3(0, 1, 0) * 50, Vector3(0,0, 0), 0.02f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);

		break;
	case 'Y':
		psistem->generateFirework(4, Vector3(0, 2, 0), Vector3(0, 1, 0) * 80, Vector3(0,0, 0), 0.02f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
		break;
	case 'E':
		psistem->generateFirework(1, Vector3(0, 2, 300), Vector3(0, 1, 0) * 80, Vector3(0, 0, 0), 0.02f, 3, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
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