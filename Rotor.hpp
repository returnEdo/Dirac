#pragma once

#include <cmath>
#include <iostream>

#include "vec3.hpp"
#include "mat3.hpp"


namespace Dirac
{

namespace Math
{


class Rotor
{
	private:

	mat3 tMatrixForm;
	static constexpr float mNEAR_TOLL = .00001;

	public:
	
	float a;
	float b;
	float c;
	float d;

	Rotor(float tA, float tB, float tC, float tD):
		a(tA),	b(tB),	c(tC), 	d(tD)			{}

	Rotor(const Rotor& tRotor):
		Rotor(tRotor.a, tRotor.b, tRotor.c, tRotor.d)	{}

	Rotor(float tTheta, const vec3& tK)
	{
		a = cos(tTheta / 2.0f);	
		
		float lsinTheta2 = sin(tTheta / 2.0f);
		b = tK.z * lsinTheta2;
		c = tK.x * lsinTheta2;
		d = tK.y * lsinTheta2;
	}

	inline mat3& getMatrix(void)		{ return tMatrixForm; }
	inline float getNorm(void) const	{ return std::sqrt(a*a + b*b + c*c + d*d); }
	
	void updateMatrix(void);
	void normalize(void);
	
	friend std::ostream& operator <<(std::ostream& tOs, Rotor& tRotor);
};



};

};
