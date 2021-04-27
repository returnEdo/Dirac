#pragma once

#include <string>

#include "Entity.h"
#include "System.h"
#include "IRenderer.h"
#include "Shader.h"
#include "DiracMacros.h"


namespace Dirac
{


struct TextureDataLayout
{
	// Specifies the layout of the vertex buffer
	// used by the TextureRenderer
	
	float mVertexPosition[3];
	float mVertexNormal[3];
	float mVertexUV[2];
};

/*
SIGNATURE:
-Transform
-Texture
*/

class TextureRenderer: public ISystem, public IRenderer
{
	private:
	
	unsigned int mTextureID { };

	// Texture attributes
	int mTextureWidth { };
	int mTextureHeight { };
	int mTextureChannels { };
	
	public:

	void init(const std::string& tTextureAtlasAddress);

	virtual void init(void) override { DIRAC_ASSERT(false, "Not avalilable for texture rendering!!"); }
	virtual void update(EntityID tCameraID) override;
	virtual void destroy(void) override;
};




};
