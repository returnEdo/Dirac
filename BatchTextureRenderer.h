#pragma once

#include <string>
#include <memory>

#include "Entity.h"
#include "System.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "DiracMacros.h"
#include "RenderingComponents.h"


namespace Dirac
{



namespace Models
{
	// Quad vertex buffer
	extern TextureVertex 	nQuadVertex[4];

	// Quad index buffer
	extern unsigned int	nQuadIndex[6]; 
};


/*
SIGNATURE:
-Transform
-Texture
*/

class BatchTextureRenderer: public ISystem
{
	private:

	Graphics::Texture*	mTexture	{ nullptr };
	Graphics::Shader*	mShader		{ nullptr };
	Graphics::Buffer*	mVertexBuffer	{ nullptr };
	Graphics::Buffer*	mIndexBuffer	{ nullptr };
	Graphics::VertexArray*	mVertexArray	{ nullptr };

	public:

	BatchTextureRenderer(void):
					mTexture(nullptr),
					mShader(nullptr),
					mVertexBuffer(nullptr),
					mIndexBuffer(nullptr),
					mVertexArray(nullptr)	{}

	void init(const std::string& tTextureAtlasAddress);
	void update(EntityID tCameraID);
	void destroy(void); 
};




};
