#pragma once

#include <vector>
#include <string>

#include "DiracConstants.h"
#include "Vector.h"
#include "Vector2.h"
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


struct Texture
{	
	// Texture coordinates of the quad
	Vector2 mBottomLeft;

	float mWidth;		// e.g.: 32 bit
	float mHeight;
};


struct Line
{
	Vector mVertexA;
	Vector mVertexB;
};


};
