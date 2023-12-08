#pragma once
#include "RenderUtils.hpp"
using namespace std;
using namespace physx;
//CLASE BASE SOLIDOS RIGIDOS 
class RigidBody
{
	public:
		PxRigidBody* body;
		RenderItem* item;
		PxShape* shape;
		float time = 0;
		float tolive;
};
class StaticRigidBody
{
public:
	PxRigidStatic* body;
	RenderItem* item;
	PxShape* shape;
	float time = 0;
};
