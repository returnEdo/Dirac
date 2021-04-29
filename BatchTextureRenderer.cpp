#include "BatchTextureRenderer.h"

#include <cstddef>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "DiracConstants.h"
#include "Manager.h"


extern Dirac::Manager gManager;

namespace Dirac
{


namespace Models
{
	// Quad vertex buffer
	TextureVertex 	nQuadVertex[] =
	{
		{Vector(-0.5f, -0.5f, 0.0f), Vector2(0.0f, 0.0f)},
		{Vector( 0.5f, -0.5f, 0.0f), Vector2(1.0f, 0.0f)},
		{Vector( 0.5f,  0.5f, 0.0f), Vector2(1.0f, 1.0f)},
		{Vector(-0.5f,  0.5f, 0.0f), Vector2(0.0f, 1.0f)}
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
	mShader = new Graphics::Shader("resources/shaders/textureVertex.shader",
			     	       "resources/shaders/textureFragment.shader");
	
	mVertexArray	= new Graphics::VertexArray();
	mVertexBuffer 	= new Graphics::Buffer(GL_ARRAY_BUFFER); 
	mIndexBuffer 	= new Graphics::Buffer(GL_ELEMENT_ARRAY_BUFFER);
	// Generate buffers

	mVertexBuffer -> allocate(sizeof(Models::nQuadVertex) * Constants::MAX_VERTICES_BATCH);
	mIndexBuffer ->  allocate(sizeof(Models::nQuadIndex) * Constants::MAX_VERTICES_BATCH);

	mVertexArray -> addAttribute(Models::nAttributePosition);
	mVertexArray -> addAttribute(Models::nAttributeTextureUV);

	// Texture atlas
	mTexture = new Graphics::Texture(tTextureAtlasAddress);

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
	Matrix lCameraAttitudeT = transpose(lCameraTransform.mAttitude);

	mTexture -> bind();
	mShader -> bind();
	mVertexArray -> bind();
	mVertexBuffer -> bind();
	mIndexBuffer -> bind();

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
		// Retrieve components
		Transform& lEntityTransform 	= gManager.getComponent<Transform>(entity);	// world coordinates
		Texture& lTexture		= gManager.getComponent<Texture>(entity);
		
		for (const TextureVertex& vertex: Models::nQuadVertex)
		{	
			lVertex.mPosition 	= lCameraAttitudeT * (lEntityTransform.mAttitude * (lEntityTransform.mShear * vertex.mPosition) + lEntityTransform.mPosition - lCameraTransform.mPosition);
			lVertex.mTextureUV	= lTexture.mBottomLeft + Vector2(vertex.mTextureUV.x * lTexture.mWidth,
										 vertex.mTextureUV.y * lTexture.mHeight);

			lVertex.mTextureUV.x 	/= lTextureWidth_float;
			lVertex.mTextureUV.y 	/= lTextureHeight_float;

			// Filling the buffer
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


void BatchTextureRenderer::destroy(void)
{
	delete mShader;
	delete mVertexBuffer;
	delete mIndexBuffer;
	delete mTexture;
	delete mVertexArray;
}


};
