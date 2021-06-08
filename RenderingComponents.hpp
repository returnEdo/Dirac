#pragma once

#include <vector>
#include <string>

#include "DiracConstants.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mat3.hpp"
#include "Rotor.hpp"



namespace Dirac
{


// Vertex data layout
struct Vertex
{
	Math::vec3 mPosition;
	Math::vec3 mNormal;
	Math::vec3 mColor;
	float      mAlpha;
};

struct LineVertex
{	
	Math::vec3 mPosition;
	Math::vec3 mColor;
	float      mAlpha;
};

struct TextureVertex
{
	Math::vec3 mPosition;
	Math::vec2 mTextureUV;
	float 	   mAlpha;
};


// Components
struct Transform
{
	Math::vec3 	mPosition;
	Math::Rotor	mRotor;
	Math::mat3	mShear;
};


struct Color
{
	Math::vec3	mColor;
	float		mAlpha;
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
	Math::vec2 mBottomLeft;

	float mWidth;		// e.g.: 32 bit
	float mHeight;

	float mAlpha;
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
