#include "MathUtils.hpp"

#include <cmath>

namespace Dirac
{

namespace Math
{
	
float sign(float tValue)
{	
	return (tValue >= .0f? 1.0f: -1.0f);
}

float segmentOverlap(float tCenterA, float tDimensionA,
		     float tCenterB, float tDimensionB)
{
	return (fmin(tCenterA + tDimensionA / 2.0f, tCenterB + tDimensionB / 2.0f) -
		fmax(tCenterA - tDimensionA / 2.0f, tCenterB - tDimensionB / 2.0f));
}


bool areRectanglesIntersecting(const Math::vec2& tCenterA, const Math::vec2& tDimensionsA,
			       const Math::vec2& tCenterB, const Math::vec2& tDimensionsB)
{
	return ((segmentOverlap(tCenterA.x, tDimensionsA.x, tCenterB.x, tDimensionsB.x) > 0) and
		(segmentOverlap(tCenterA.y, tDimensionsA.y, tCenterB.y, tDimensionsB.y) > 0));
}


bool near(float tValue, float tReference, float tTollerance)
{
	return (std::abs(tValue - tReference) <= tTollerance);
}


Math::mat3 cross(const Math::vec3& tV)
{
	return Math::mat3(Math::vec3(0.0f, -tV.z, tV.y),
			  Math::vec3(tV.z, 0.0f, -tV.x),
			  Math::vec3(-tV.y, tV.x, 0.0f));
}


};

}
