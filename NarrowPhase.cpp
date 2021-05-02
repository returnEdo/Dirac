#include "NarrowPhase.hpp"

#include <cmath>

#include "Manager.hpp"
#include "RenderingComponents.hpp"
#include "MathUtils.hpp"
#include "DiracMacros.hpp"


extern Dirac::Manager gManager;


namespace Dirac
{

namespace Physics
{

void checkCollision(CollisionInfo& tCollisionInfo)
{
	Transform& lTransformA 	= gManager.getComponent<Transform>(tCollisionInfo.mEntityA);		
	Transform& lTransformB 	= gManager.getComponent<Transform>(tCollisionInfo.mEntityB);		
	
	AABB& lBoxA		= gManager.getComponent<AABB>(tCollisionInfo.mEntityA);
	AABB& lBoxB		= gManager.getComponent<AABB>(tCollisionInfo.mEntityB);
	
	Math::vec2 lCenterA { lTransformA.mPosition.x, lTransformA.mPosition.y };
	Math::vec2 lCenterB { lTransformB.mPosition.x, lTransformB.mPosition.y };

	float lOverlapX 	= fmin(lCenterA.x + lBoxA.mDimensions.x / 2.0f, lCenterB.x + lBoxB.mDimensions.x / 2.0f) - 
				  fmax(lCenterA.x - lBoxA.mDimensions.x / 2.0f, lCenterB.x - lBoxB.mDimensions.x / 2.0f);

	if (lOverlapX > .0f)
	{
		float lOverlapY 	= fmin(lCenterA.y + lBoxA.mDimensions.y / 2.0f, lCenterB.y + lBoxB.mDimensions.y / 2.0f) - 
					  fmax(lCenterA.y - lBoxA.mDimensions.y / 2.0f, lCenterB.y - lBoxB.mDimensions.y / 2.0f);

		if (lOverlapY > .0f)
		{
			Math::vec2 lRelativePosition = lCenterB - lCenterA;

			tCollisionInfo.mCollision 	= true;	
			
			float lCollisionX = (Math::sign(lOverlapX - lOverlapY) + 1.0f) / 2.0f;

			tCollisionInfo.mNormal = Math::vec2((1.0f - lCollisionX) * Math::sign(lRelativePosition.x),
						 	    (lCollisionX) 	 * Math::sign(lRelativePosition.y));
			
			tCollisionInfo.mPenetration 	= fmin(lOverlapX, lOverlapY);
			tCollisionInfo.mPosition 	= Math::vec2((lBoxA.mDimensions.x - lOverlapX) / 2.0f * Math::sign(lRelativePosition.x),
							  	     (lBoxA.mDimensions.y - lOverlapY) / 2.0f * Math::sign(lRelativePosition.y));
			tCollisionInfo.mPosition	+= lCenterA; 
		}
	}
}


void solvePenetration(const CollisionInfo& tCollisionInfo)
{
	Transform& lTransformA 	= gManager.getComponent<Transform>(tCollisionInfo.mEntityA);		
	Transform& lTransformB 	= gManager.getComponent<Transform>(tCollisionInfo.mEntityB);		

	Inertia& lInertiaA	= gManager.getComponent<Inertia>(tCollisionInfo.mEntityA);
	Inertia& lInertiaB	= gManager.getComponent<Inertia>(tCollisionInfo.mEntityB);
	
	Math::vec3 lNormal { tCollisionInfo.mNormal.x, tCollisionInfo.mNormal.y, 0.0f };

	float lDeltaA = tCollisionInfo.mPenetration * lInertiaB.mMass / (lInertiaA.mMass + lInertiaB.mMass);
	float lDeltaB = tCollisionInfo.mPenetration * lInertiaA.mMass / (lInertiaA.mMass + lInertiaB.mMass);

	lTransformA.mPosition	-= lDeltaA * lNormal;
	lTransformB.mPosition	+= lDeltaB * lNormal;
}


};

};
