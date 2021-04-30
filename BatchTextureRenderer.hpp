#pragma once

#include <string>
#include <memory>

#include "Entity.hpp"
#include "System.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "DiracMacros.hpp"
#include "RenderingComponents.hpp"
#include "Memory/Unique.hpp"


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

	Memory::Unique<Graphics::Texture>	mTexture;
	Memory::Unique<Graphics::Shader>	mShader;
	Memory::Unique<Graphics::Buffer>	mVertexBuffer;
	Memory::Unique<Graphics::Buffer>	mIndexBuffer;
	Memory::Unique<Graphics::VertexArray>	mVertexArray;

	public:

	void init(const std::string& tTextureAtlasAddress);
	void update(EntityID tCameraID);
};




};
