#include "ThetaMethods.hpp"

#include <cmath>

#include "Entity.hpp"
#include "Manager.hpp"
#include "PhysicsComponents.hpp"
#include "RenderingComponents.hpp"

#include "vec2.hpp"
#include "vec3.hpp"
#include "mat3.hpp"

#include "DiracMacros.hpp"

extern Dirac::Manager gManager;


namespace Dirac
{


namespace Physics
{


void ThetaMethods::integrate(float tDt)
{
	PRINT_AUTO(mEntities.size());

	for (EntityID entity: mEntities)
	{
		Transform& lTransform 		= gManager.getComponent<Transform>(entity);
		Physics::Dynamics& lDynamics	= gManager.getComponent<Physics::Dynamics>(entity);
		Physics::Forces& lForces	= gManager.getComponent<Physics::Forces>(entity);
		Physics::Inertia& lInertia	= gManager.getComponent<Physics::Inertia>(entity);

		Math::vec2 lOldVelocity 	= lDynamics.mVelocity;
		float	   lOldAngularVelocity	= lDynamics.mAngularVelocity;

		lDynamics.mVelocity		+= lForces.mForce / lInertia.mMass * tDt;
		PRINT_AUTO(lDynamics.mVelocity);
		lDynamics.mAngularVelocity	+= lForces.mTorque / lInertia.mMomentOfInertia * tDt;
	
		Math::vec2 lNewPosition 	= Math::vec2(lTransform.mPosition.x, lTransform.mPosition.y) + 
						  (mTheta * lOldVelocity + 
						  (1 - mTheta) * lDynamics.mVelocity) * tDt;

		float lNewAttitude		= fmod((atan2(lTransform.mAttitude.col1.y, lTransform.mAttitude.col1.x) + 
						  (mTheta * lOldAngularVelocity + 
						  (1 - mTheta) * lDynamics.mAngularVelocity) * tDt), 2.0f * M_PI);

		lTransform.mPosition.x 		= lNewPosition.x;
		lTransform.mPosition.y 		= lNewPosition.y;

		lTransform.mAttitude		= Math::mat3(Math::vec3(0.0f, 0.0f, 1.0f), lNewAttitude);
	}

}


};


};
