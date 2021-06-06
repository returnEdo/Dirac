#include "Rotor.hpp"
#include "mat3.hpp"
#include "vec3.hpp"
#include "DiracMacros.hpp"

#include <iostream>
#include <cmath>

using namespace Dirac::Math;


int main()
{
	
	Rotor rotor0(M_PI / 3, vec3(0.0f, .0f, 1.0f));
	rotor0.updateMatrix();

	PRINT_AUTO(rotor0.getMatrix());
	PRINT_AUTO(rotor0.getNorm());


	PRINT_AUTO(rotor0);

	return 0;
};
