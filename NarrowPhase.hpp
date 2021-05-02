#pragma once

#include "vec2.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "PhysicsComponents.hpp"


namespace Dirac
{

namespace Physics
{


struct CollisionInfo
{
	EntityID 	mEntityA;
	EntityID 	mEntityB;

	Math::vec2 	mPosition;		// world position
	Math::vec2 	mNormal;

	float 		mPenetration;
	bool 		mCollision = false;
};

/*
SIGNATURE:
- Transform
- AABB
*/
void checkCollision(CollisionInfo& tCollisionInfo);

/*
SIGNATURE:
- Transform
- Inertia
*/
void solvePenetration(const CollisionInfo& tCollisionInfo);

};

};
