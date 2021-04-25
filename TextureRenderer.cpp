#include "TextureRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "DiracConstants.h"
#include "DiracMacros.h"
#include "RenderingComponents.h"
#include "Manager.h"

#include "DiracMacros.h"

extern Dirac::Manager gManager;

namespace Dirac
{

namespace TextureRawBuffers
{
	// Buffers used below

	// Vertex position and normal
	float mVertexData[] =
	{
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f
	};

	// Index buffer
	unsigned int mIndexData[] =
	{
		0, 1, 2, 		
		0, 2, 3
	};
};


TextureRenderer::~TextureRenderer(void)
{
	delete mShader;

	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void TextureRenderer::init(const std::string& tTextureAtlasAddress)
{
	// Compile shader
	mShader = new Shader("resources/shaders/textureVertex.shader",
			     "resources/shaders/textureFragment.shader");
	

	// Generate buffers
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	glGenBuffers(1, &mVertexBufferID);
	glGenBuffers(1, &mIndexBufferID);

	// Load data into the GPU
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TextureRawBuffers::mVertexData),
		     TextureRawBuffers::mVertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TextureRawBuffers::mIndexData),
		     TextureRawBuffers::mIndexData, GL_STATIC_DRAW);

	
	// Specifies data layout
	// Vertex position
	glVertexAttribPointer(0, sizeof(TextureDataLayout::mVertexPosition) / sizeof(float),
			      GL_FLOAT, GL_FALSE, sizeof(TextureDataLayout),
			      (void*)0);
	glEnableVertexAttribArray(0);
	
	// Vertex normal
	glVertexAttribPointer(1, sizeof(TextureDataLayout::mVertexNormal) / sizeof(float),
			      GL_FLOAT, GL_FALSE, sizeof(TextureDataLayout),
			      (void*)(sizeof(TextureDataLayout::mVertexPosition)));
	glEnableVertexAttribArray(1);
	
	// Vertex texture coordinate
	glVertexAttribPointer(2, sizeof(TextureDataLayout::mVertexUV) / sizeof(float),
			      GL_FLOAT, GL_FALSE, sizeof(TextureDataLayout),
			      (void*)(sizeof(TextureDataLayout::mVertexPosition) + sizeof(TextureDataLayout::mVertexNormal)));
	glEnableVertexAttribArray(2);



	// Texture atlas
	glGenTextures(1, &mTextureID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	// Texture wrapping options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// flip the fucking texture
	stbi_set_flip_vertically_on_load(true);

	// Load data from file
	unsigned char *lTextureData = stbi_load(tTextureAtlasAddress.c_str(), &mTextureWidth, &mTextureHeight, &mTextureChannels, 0);

	DIRAC_ASSERT((lTextureData != nullptr), "Failed to load texture!!");

	unsigned int DATA_TYPE = (mTextureChannels == 3? GL_RGB: GL_RGBA);

	// Load data in GPU
	glTexImage2D(GL_TEXTURE_2D, 0, DATA_TYPE, mTextureWidth, mTextureHeight, 0, DATA_TYPE, GL_UNSIGNED_BYTE, lTextureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(lTextureData);

	mShader -> bind();
	glUniform1i(glGetUniformLocation(mShader -> getID(), "uTextureAtlas"), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void TextureRenderer::update(EntityID tCameraID)
{

	Transform lCameraTransform = gManager.getComponent<Transform>(tCameraID);
	View lCameraView = gManager.getComponent<View>(tCameraID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	mShader -> bind();
	glBindVertexArray(mVertexArrayID);

	// camera transform uniforms
	mShader -> setUniform("uCameraPosition", lCameraTransform.mPosition);
	mShader -> setUniform("uCameraAttitude", lCameraTransform.mAttitude);

	// camera view uniforms
	mShader -> setUniform("uCameraDeltax", lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", lCameraView.mAspectRatio);

	float lWidth_float = static_cast<float>(mTextureWidth);
	float lHeight_float = static_cast<float>(mTextureHeight);

	for (auto lEntity: mEntities)
	{
		auto lEntityTransform = gManager.getComponent<Transform>(lEntity);
		auto lEntityTexture = gManager.getComponent<Texture>(lEntity);

		// entity transform uniforms
		mShader -> setUniform("uEntityPosition", lEntityTransform.mPosition);
		mShader -> setUniform("uEntityAttitude", lEntityTransform.mAttitude);
		mShader -> setUniform("uEntityShear", lEntityTransform.mShear);
	
		// entity color uniforms
		mShader -> setUniform("uTextureCoordBL", Vector2(lEntityTexture.mBottomLeft.x / lWidth_float,
							  	 lEntityTexture.mBottomLeft.y / lHeight_float));
		mShader -> setUniform("uTextureWidth", (lEntityTexture.mWidth / lWidth_float));
		mShader -> setUniform("uTextureHeight", (lEntityTexture.mHeight / lHeight_float));


		glDrawElements(GL_TRIANGLES,
			       sizeof(TextureRawBuffers::mIndexData) / sizeof(unsigned int),
			       GL_UNSIGNED_INT,
			       0);
	}
}


};
