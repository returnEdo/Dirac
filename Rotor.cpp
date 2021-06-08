#include "Rotor.hpp"

#include <cmath>

#include "DiracMacros.hpp"
#include "MathUtils.hpp"


namespace Dirac
{

namespace Math
{


Math::mat3 Rotor::getMatrixForm(void)
{
	Math::mat3 lMat;

	lMat.row1 = Math::vec3(a*a - b*b + c*c - d*d,
	          	       2.0f * (-a*b + c*d),
	         	       2.0f * (a*d + b*c));
	lMat.row2 = Math::vec3(2.0f * (a*b + c*d),
	         	       a*a - b*b - c*c + d*d,
	         	       2.0f * (-a*c + b*d));
	lMat.row3 = Math::vec3(2.0f * (-a*d + b*c),
			       2.0f * (a*c + b*d),
			       a*a + b*b - c*c - d*d);

	lMat.buildCol();

	return lMat;
}

void Rotor::normalize(void)
{
	float lNorm = getNorm();
	
	DIRAC_ASSERT(not near(lNorm, 0.0, mNEAR_TOLL), "Normalizing zero norm rotor!!");

	a /= lNorm;
	b /= lNorm;
	c /= lNorm;
	d /= lNorm;
}


std::ostream& operator <<(std::ostream& tOs, Rotor& tRotor)
{
	tOs << "(" << tRotor.a << ", " << tRotor.b << ", "
	    << tRotor.c << ", "  << tRotor.d << ")";
	
	return tOs;

}


};


};
