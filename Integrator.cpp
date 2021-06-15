#include "Integrator.hpp"

#include <cmath>

#include "Manager.hpp"
#include "MathUtils.hpp"
#include "DiracMacros.hpp"


extern Dirac::Manager gManager;


namespace Dirac
{

namespace Physics
{


void Integrator::updateEntity(EntityID tID, float tDt)
{
	Transform& lTransform 	= gManager.getComponent<Transform>(tID);
	Dynamics& lDynamics	= gManager.getComponent<Dynamics>(tID);
	Forces& lForces		= gManager.getComponent<Forces>(tID);
	Inertia& lInertia	= gManager.getComponent<Inertia>(tID);

	Math::mat3 lIdentity;

	// STEP 1: angular velocity integration
	Math::mat3 lAomega = (lInertia.mInertia / tDt -
			      Math::cross(lInertia.mInertia * lDynamics.mOmega) * mTheta +
			      lIdentity * lForces.mCRotational * mTheta);

	Math::mat3 lBomega = (lInertia.mInertia / tDt +
			      Math::cross(lInertia.mInertia * lDynamics.mOmega) * (1.0 - mTheta) -
			      lIdentity * lForces.mCRotational * (1.0 - mTheta));
	
	lDynamics.mOmega = inv(lAomega) * (lBomega * lDynamics.mOmega + transpose(lTransform.mRotor.getMatrixForm()) * lForces.mTorque);

	// STEP 2: rotor update
	Math::Rotor 	rot = lTransform.mRotor;
	Math::vec3	om  = lDynamics.mOmega;

	lTransform.mRotor.a = rot.a - tDt / 2.0f * (rot.b * om.z + rot.c * om.x + rot.d * om.y);
	lTransform.mRotor.b = rot.b + tDt / 2.0f * (rot.a * om.z + rot.c * om.y - rot.d * om.x);
	lTransform.mRotor.c = rot.c + tDt / 2.0f * (rot.a * om.x - rot.b * om.y + rot.d * om.z);
	lTransform.mRotor.d = rot.d + tDt / 2.0f * (rot.a * om.y + rot.b * om.x - rot.c * om.z);

	lTransform.mRotor.normalize();

	
	// STEP 3: velocity update
	Math::vec3 lVold = lDynamics.mVelocity;

	float lAlpha = 1.0f / tDt + lForces.mCLinear * mTheta / lInertia.mMass;
	float lBeta  = 1.0f / tDt - lForces.mCLinear * (1.0f - mTheta) / lInertia.mMass;

	lDynamics.mVelocity = (lBeta * lDynamics.mVelocity + lForces.mForce / lInertia.mMass) / lAlpha;

	// STEP 4: position update
	lTransform.mPosition += tDt * (mTheta * lDynamics.mVelocity + (1.0f - mTheta) * lVold);

	// STEP 5: clear forces
	lForces.clear();
}


void Integrator::update(float tDt)
{
	for (EntityID lID: mEntities)
	{
		updateEntity(lID, tDt);
	}
}



};

};
