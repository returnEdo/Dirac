#pragma once

#include "System.hpp"



namespace Dirac
{


namespace Physics
{

/*
Theta integration methods

Signature:
- Dynamics
- Forces
- Inertia
- Transform
*/

class ThetaMethods: public ISystem
{
	private:

	float mTheta = 0.0f;

	public:

	inline void setTheta(float tTheta)	{ mTheta = tTheta; }

	void integrate(float tDt);
};



};


};
