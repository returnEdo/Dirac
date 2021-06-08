#pragma once

#include "RenderingComponents.hpp"
#include "PhysicsComponents.hpp"
#include "System.hpp"
#include "Entity.hpp"


namespace Dirac
{

namespace Physics
{

/*
SIGNATURE:
-Transform
-Dynamics
-Intertia
-Forces
*/
class Integrator: public ISystem
{
	private:

	// Defaults to CN
	float mTheta { 0.5f };

	public:

	inline void setTheta(float tTheta)	{ mTheta = tTheta; }

	void updateEntity(EntityID tID, float tDt);
	void update(float tDt);

};


};

};
