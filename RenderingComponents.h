#pragma once

#include <vector>
#include <string>

#include "DiracConstants.h"
#include "Vector.h"
#include "Matrix.h"

namespace Dirac
{


struct VertexDataLayout
{
	float mPosition[3];
	float mNormal[3];
};

struct Transform
{
	Vector 	mPosition;
	Matrix 	mAttitude;
	Matrix	mShear;
};


struct Color
{
	Vector	mColor;
	float	mAlpha;
};


struct View
{
	float mDeltax		= Constants::DELTAX;
	float mDeltaz		= Constants::DELTAZ;
	float mAspectRatio	= Constants::ASPECT_RATIO;
	float mNearPlane	= Constants::NEAR_PLANE;
};


};
