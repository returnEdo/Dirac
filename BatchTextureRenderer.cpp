#include "BatchTextureRenderer.hpp"

#include <cstddef>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "DiracConstants.hpp"
#include "Manager.hpp"
#include "mat3.hpp"


extern Dirac::Manager gManager;

namespace Dirac
{


namespace Models
{
	// Quad vertex buffer
	TextureVertex 	nQuadVertex[] =
	{
		{Math::vec3(-0.5f, -0.5f, 0.0f), Math::vec2(0.0f, 0.0f)},
		{Math::vec3( 0.5f, -0.5f, 0.0f), Math::vec2(1.0f, 0.0f)},
		{Math::vec3( 0.5f,  0.5f, 0.0f), Math::vec2(1.0f, 1.0f)},
		{Math::vec3(-0.5f,  0.5f, 0.0f), Math::vec2(0.0f, 1.0f)}
	};

	// Quad index buffer
	unsigned int	nQuadIndex[] = 
	{
		0, 1, 2,
		2, 3, 0
	};

	Graphics::Attribute nAttributePosition  {DIRAC_COUNT(TextureVertex::mPosition, float), GL_FLOAT, sizeof(TextureVertex), offsetof(TextureVertex, mPosition)};
	Graphics::Attribute nAttributeTextureUV {DIRAC_COUNT(TextureVertex::mTextureUV, float), GL_FLOAT, sizeof(TextureVertex), offsetof(TextureVertex, mTextureUV)};
};

void BatchTextureRenderer::init(const std::string& tTextureAtlasAddress)
{
	// Compile shader
	mShader.allocate(new Graphics::Shader("resources/shaders/textureVertex.shader",
				     	      "resources/shaders/textureFragment.shader"));
	
	mVertexArray.allocate(new Graphics::VertexArray());
	mVertexBuffer.allocate(new Graphics::Buffer(GL_ARRAY_BUFFER)); 
	mIndexBuffer.allocate(new Graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER));
	// Generate buffers

	mVertexBuffer -> allocate(sizeof(Models::nQuadVertex) * Constants::MAX_VERTICES_BATCH);
	mIndexBuffer ->  allocate(sizeof(Models::nQuadIndex) * Constants::MAX_VERTICES_BATCH);

	mVertexArray -> addAttribute(Models::nAttributePosition);
	mVertexArray -> addAttribute(Models::nAttributeTextureUV);

	// Texture atlas
	mTexture.allocate(new Graphics::Texture(tTextureAtlasAddress));

	mShader -> bind();
	mShader -> setUniform("uTextureAtlas", 0);

	mVertexArray -> bind(false);
	mVertexBuffer -> bind(false);
	mIndexBuffer -> bind(false);
}


void BatchTextureRenderer::update(EntityID tCameraID)
{
	Transform lCameraTransform = gManager.getComponent<Transform>(tCameraID);
	View lCameraView = gManager.getComponent<View>(tCameraID);
	Math::mat3 lCameraAttitudeT = transpose(lCameraTransform.mAttitude);

	mTexture 	-> bind();
	mShader 	-> bind();
	mVertexArray 	-> bind();
	mVertexBuffer 	-> bind();
	mIndexBuffer 	-> bind();

	// camera view uniforms
	mShader -> setUniform("uCameraDeltax", 		lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", 		lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", 		lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", 	lCameraView.mAspectRatio);

	TextureVertex* lMapBuffer 	= mVertexBuffer -> getBuffer<TextureVertex>();
	unsigned int*  lMapIndexBuffer 	= mIndexBuffer -> getBuffer<unsigned int>();

	float lTextureWidth_float	= mTexture -> getWidth();
	float lTextureHeight_float	= mTexture -> getHeight();

	unsigned int lCurrentVertex	= 0;
	unsigned int indexCount		= 0;

	TextureVertex lVertex;
	
	for (auto entity: mEntities)
	{
		Transform& lEntityTransform 	= gManager.getComponent<Transform>(entity);	// world coordinates
		Texture& lTexture		= gManager.getComponent<Texture>(entity);
		
		for (const TextureVertex& vertex: Models::nQuadVertex)
		{	
			lVertex.mPosition 	= lCameraAttitudeT * (lEntityTransform.mAttitude * (lEntityTransform.mShear * vertex.mPosition) + lEntityTransform.mPosition - lCameraTransform.mPosition);
			lVertex.mTextureUV	= lTexture.mBottomLeft + Math::vec2(vertex.mTextureUV.x * lTexture.mWidth,
										 vertex.mTextureUV.y * lTexture.mHeight);
			lVertex.mTextureUV.x 	/= lTextureWidth_float;
			lVertex.mTextureUV.y 	/= lTextureHeight_float;

			memcpy((lMapBuffer + lCurrentVertex), &lVertex, sizeof(TextureVertex));
			
			lCurrentVertex ++;
		}

		for (int k = 0; k < 6; k++)
		{
			lMapIndexBuffer[6 * indexCount + k] = Models::nQuadIndex[k] + indexCount * 4;
		}
		indexCount ++;
		
	}
	mVertexBuffer -> unmapBuffer();
	mIndexBuffer -> unmapBuffer();

	glDrawElements(GL_TRIANGLES,
		       mEntities.size() * 6,
		       GL_UNSIGNED_INT,
		       0);
}


};
