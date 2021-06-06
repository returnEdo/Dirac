#pragma once

#include "vec3.hpp"
#include "mat3.hpp"


namespace Dirac
{

namespace Physics
{


struct Dynamics
{
	Math::vec3	mVelocity;
	Math::vec3	mOmega;			// angular velocity
};


struct Forces
{
	Math::vec3 	mForce;
	Math::vec3	mTorque;
};


struct Inertia
{	
	float		mMass;
	Math::mat3	mInertia;
};

};

};
