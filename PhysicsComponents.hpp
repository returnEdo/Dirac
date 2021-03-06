#pragma once

#include "vec2.hpp"


namespace Dirac
{

namespace Physics
{

// Axis Aligned Bounding Box
struct AABB
{
	Math::vec2 mDimensions;
};


struct Dynamics
{
	Math::vec2	mVelocity;
	float 		mAngularVelocity;	// positive cc
};


struct Forces
{
	Math::vec2 	mForce;
	float 		mTorque;
};


struct Inertia
{	
	float	mMass;
	float 	mMomentOfInertia;
};

};

};
