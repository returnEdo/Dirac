#include "DynamicBatchRenderer.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <cstring>

#include "Shader.hpp"
#include "Manager.hpp"
#include "DiracMacros.hpp"
#include "mat3.hpp"


extern Dirac::Manager gManager;


namespace Dirac
{


namespace Models
{

namespace VertexAttributes
{
	Graphics::Attribute nDynamicBatchPosition {DIRAC_COUNT(Vertex::mPosition, float), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, mPosition)};
	Graphics::Attribute nDynamicBatchNormal   {DIRAC_COUNT(Vertex::mNormal, float), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, mNormal)};
	Graphics::Attribute nDynamicBatchColor 	  {DIRAC_COUNT(Vertex::mColor, float), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, mColor)};
	Graphics::Attribute nDynamicBatchAlpha 	  {DIRAC_COUNT(Vertex::mAlpha, float), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, mAlpha)};
};

};


void DynamicBatchRenderer::init(void)
{
	// Shader
	mShader.allocate(new Graphics::Shader("./resources/shaders/batchVertex.shader",
			  	       	      "./resources/shaders/batchFragment.shader"));
	
	mVertexArray.allocate(new Graphics::VertexArray());
	mVertexBuffer.allocate(new Graphics::Buffer(GL_ARRAY_BUFFER));

	mVertexBuffer -> allocate(Constants::MAX_VERTICES_BATCH * sizeof(Vertex));

	// Specify data layout
	mVertexArray -> addAttribute(Models::VertexAttributes::nDynamicBatchPosition);
	mVertexArray -> addAttribute(Models::VertexAttributes::nDynamicBatchNormal);
	mVertexArray -> addAttribute(Models::VertexAttributes::nDynamicBatchColor);
	mVertexArray -> addAttribute(Models::VertexAttributes::nDynamicBatchAlpha);

	// Unbinding
	mVertexBuffer 	-> bind(false);
	mVertexArray 	-> bind(false);
}


void DynamicBatchRenderer::update(EntityID tCameraID)
{
	// update uniform + draw call
	mShader 	-> bind();
	mVertexBuffer 	-> bind();
	mVertexArray 	-> bind();

	auto lCameraTransform 	= gManager.getComponent<Transform>(tCameraID);
	auto lCameraView 	= gManager.getComponent<View>(tCameraID);

	// camera view uniforms
	mShader -> setUniform("uCameraDeltax", 		lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", 		lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", 		lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", 	lCameraView.mAspectRatio);

	Vertex* lMapBuffer = mVertexBuffer -> getBuffer<Vertex>();

	Vertex lVertex;

	unsigned int lCurrentVertex = 0;
	
	Math::mat3 lCameraAttitudeT = transpose(lCameraTransform.mAttitude);
	
	for (EntityID entity: mEntities)
	{
		// Retrieve components
		Model& lModel 			= gManager.getComponent<Model>(entity);		// cam coordinates
		Transform& lEntityTransform 	= gManager.getComponent<Transform>(entity);	// world coordinates
		Color& lColor 			= gManager.getComponent<Color>(entity);

		for (const Vertex& vertex: *lModel.mPVertices)
		{
			// Position and normal in camera view
			lVertex.mPosition 	= lCameraAttitudeT * (lEntityTransform.mAttitude * (lEntityTransform.mShear * vertex.mPosition) + lEntityTransform.mPosition - lCameraTransform.mPosition);
			lVertex.mNormal 	= lEntityTransform.mAttitude * vertex.mNormal;
			lVertex.mColor 		= lColor.mColor;
			lVertex.mAlpha 		= lColor.mAlpha;

			memcpy((lMapBuffer + lCurrentVertex), &lVertex, sizeof(Vertex));

			lCurrentVertex ++;
		}

	}


	mVertexBuffer -> unmapBuffer();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(Vertex) * lCurrentVertex);

}

};
