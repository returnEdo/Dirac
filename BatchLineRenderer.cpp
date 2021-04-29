#include "BatchLineRenderer.h"

#include <GL/glew.h>
#include <cstddef>
#include <cstring>

#include "DiracConstants.h"
#include "DiracMacros.h"
#include "Shader.h"
#include "Manager.h"



extern Dirac::Manager gManager;

namespace Dirac
{


namespace Models
{

namespace VertexAttributes
{
	
	Graphics::Attribute nLinePosition {DIRAC_COUNT(LineVertex::mPosition, float), GL_FLOAT, sizeof(LineVertex), offsetof(LineVertex, mPosition)};
	Graphics::Attribute nLineColor	  {DIRAC_COUNT(LineVertex::mColor, float),    GL_FLOAT, sizeof(LineVertex), offsetof(LineVertex, mColor)};
};


};


void BatchLineRenderer::init(void)
{
	
	mShader = new Graphics::Shader("./resources/shaders/lineVertex.shader",
			     	       "./resources/shaders/lineFragment.shader");

	mVertexArray 	= new Graphics::VertexArray();
	mVertexBuffer 	= new Graphics::Buffer(GL_ARRAY_BUFFER);
	
	mVertexBuffer -> allocate(sizeof(LineVertex) * Constants::MAX_VERTICES_BATCH);

	mVertexArray -> addAttribute(Models::VertexAttributes::nLinePosition);
	mVertexArray -> addAttribute(Models::VertexAttributes::nLineColor);
			      
	mVertexBuffer -> bind(false);
	mVertexArray -> bind(false);
}


void BatchLineRenderer::update(EntityID tCameraID)
{
	mShader 	-> bind();
	mVertexArray 	-> bind();
	mVertexBuffer	-> bind();
	
	auto lCameraTransform = gManager.getComponent<Transform>(tCameraID);
	auto lCameraView = gManager.getComponent<View>(tCameraID);
	
	Matrix lCameraAttitudeT = transpose(lCameraTransform.mAttitude);

	mShader -> setUniform("uCameraDeltax", lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", lCameraView.mAspectRatio);

	// Pointer to Vertex buffer data
	LineVertex* lMapBuffer = mVertexBuffer -> getBuffer<LineVertex>();

	LineVertex lLineVertex;

	unsigned int lCurrentVertex = 0;

	for (EntityID entity: mEntities)
	{	

		if (lCurrentVertex  + 2 > Constants::MAX_VERTICES_BATCH)
		{
			break;
		}
		Line& lLine = gManager.getComponent<Line>(entity);
 		
		// Update vertex A
		lLineVertex.mPosition = lCameraAttitudeT * (lLine.mVertexA.mPosition - lCameraTransform.mPosition);
		lLineVertex.mColor = lLine.mVertexA.mColor;

		memcpy((lMapBuffer + lCurrentVertex), &lLineVertex, sizeof(LineVertex));
		lCurrentVertex ++;

		// Update vertex B
		lLineVertex.mPosition = lCameraAttitudeT * (lLine.mVertexB.mPosition - lCameraTransform.mPosition);
		lLineVertex.mColor = lLine.mVertexB.mColor;

		memcpy((lMapBuffer + lCurrentVertex), &lLineVertex, sizeof(LineVertex));
		lCurrentVertex ++;

	}

	mVertexBuffer -> unmapBuffer();

	glLineWidth(mLineWidth);
	glDrawArrays(GL_LINES, 0, lCurrentVertex);
}


void BatchLineRenderer::destroy(void)
{
	delete mVertexBuffer;
	delete mVertexArray;
	delete mShader;
}



};
