#include "Rotor.hpp"

#include <cmath>

#include "DiracMacros.hpp"
#include "MathUtils.hpp"


namespace Dirac
{

namespace Math
{


void Rotor::updateMatrix(void)
{
	// Matrix representation of the rotor

	tMatrixForm.row1 = Math::vec3(a*a - b*b + c*c - d*d,
				      2.0f * (-a*b + c*d),
				      2.0f * (a*d + b*c));
	tMatrixForm.row2 = Math::vec3(2.0f * (a*b + c*d),
				      a*a - b*b - c*c + d*d,
				      2.0f * (-a*c + b*d));
	tMatrixForm.row3 = Math::vec3(2.0f * (-a*d + b*c),
				      2.0f * (a*c + b*d),
				      a*a + b*b - c*c - d*d);

	tMatrixForm.buildCol();
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
