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

	// Damping constants
	float 		mCRotational 	{ 0.0 };
	float		mCLinear	{ 0.0 };

	void clear(void)
	{	
		mForce 	= Math::vec3();
		mTorque	= Math::vec3();
	}
};


struct Inertia
{	
	float		mMass;
	Math::mat3	mInertia;
};

};

};
