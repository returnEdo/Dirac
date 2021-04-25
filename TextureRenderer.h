#pragma once

#include <string>

#include "Entity.h"
#include "System.h"
#include "Shader.h"


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

class TextureRenderer: public ISystem
{
	private:
	
	// OpenGL id
	unsigned int mVertexArrayID { };
	unsigned int mVertexBufferID { };
	unsigned int mIndexBufferID { };
	unsigned int mTextureID { };

	// Texture attributes
	int mTextureWidth { };
	int mTextureHeight { };
	int mTextureChannels { };

	Shader* mShader;

	public:

	~TextureRenderer(void);

	void init(const std::string& tTextureAtlasAddress);
	void update(EntityID tCameraID);
};




};
