#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <list>
#include "PxShape.h"
#include "UniformParticleGenerator.h"
#include "WindForceGenerator.h"
#include "GravityForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "SolidForceRegistry.h"


using namespace physx;
class RBManager
{
	public:
		RBManager(PxPhysics* gPhysics, PxScene* gScene);
		virtual ~RBManager();
		 RigidBody addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,
			Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave, bool ball=false, const char* name = "");
		 StaticRigidBody addStaticObject(Vector3 dimension, Vector4 color, Vector3 transform, PxQuat rotate, bool ball=false, const char* name="");
		void createscene();
		void update(double t);
		void addForce();
	private:
		
		std::list<RigidBody> _objects;
		std::list<StaticRigidBody> _statics;
		UniformParticleGenerator* _generator;
		WindForceGenerator* windForceGen;
		GravityForceGenerator* gravityForceGen;
		AnchoredSpringFG* anchoredForceGen;
		PxPhysics* _gPhysics;
		PxScene* _gScene;
		SolidForceRegistry* _sFR;

		
		int num = 0;
		

};
