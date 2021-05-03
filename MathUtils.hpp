#pragma once

#include "vec2.hpp"

namespace Dirac
{

namespace Math
{
	
float sign(float tValue);

template <typename T>
T sign(T tValue)
{
	return (T)((tValue > T(0)) - (tValue < T(0)));
}

// if negative no overlap
float segmentOverlap(float tCenterA, float tDimensionA,
		     float tCenterB, float tDimensionB);


bool areRectanglesIntersecting(const Math::vec2& tCenterA, const Math::vec2& tDimensionsA,
			       const Math::vec2& tCenterB, const Math::vec2& tDimensionsB);


};

};
