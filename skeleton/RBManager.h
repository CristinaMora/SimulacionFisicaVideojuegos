#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <list>
#include "PxShape.h"
#include "UniformParticleGenerator.h"
#include "WindForceGenerator.h"
#include "SolidForceRegistry.h"


using namespace physx;
class RBManager
{
	public:
		RBManager(PxPhysics* gPhysics, PxScene* gScene);
		virtual ~RBManager();
		void addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,
			Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave);
		void addStaticObject();
		void update(double t);
		void addForce();
	private:
		
		std::list<RigidBody> _objects;
		UniformParticleGenerator* _generator;
		//RigidForceRegistry* reg;
		WindForceGenerator* windForceGen;
		
		PxPhysics* _gPhysics;
		PxScene* _gScene;
		PxRigidDynamic* object;
		SolidForceRegistry* _sFR;
		
		int num = 0;
		

};
