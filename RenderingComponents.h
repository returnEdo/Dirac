#pragma once

#include <vector>
#include <string>

#include "DiracConstants.h"
#include "Vector.h"
#include "Vector2.h"
#include "Matrix.h"



namespace Dirac
{


// Vertex data layout
struct Vertex
{
	Vector mPosition;
	Vector mNormal;
	Vector mColor;
};

struct LineVertex
{	
	Vector mPosition;
	Vector mColor;
};

struct TextureVertex
{
	Vector mPosition;
	Vector2 mTextureUV;
};


// Components
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
	LineVertex mVertexA;
	LineVertex mVertexB;
};


struct Model
{
	std::vector<Vertex>* mPVertices;
};


};
