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



void BatchLineRenderer::init(void)
{
	
	// Compile shader
	mShader = new Shader("./resources/shaders/lineVertex.shader",
			     "./resources/shaders/lineFragment.shader");

	// Generate and bind buffers
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	
	// Fill with data

	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(LineVertex) * Constants::MAX_VERTICES_BATCH,
		     nullptr,
		     GL_DYNAMIC_DRAW);

	// Data layout
	glVertexAttribPointer(0,
			      DIRAC_COUNT(LineVertex::mPosition, float),
			      GL_FLOAT,
			      GL_FALSE,
			      sizeof(LineVertex),
			      (void*)(offsetof(LineVertex, mPosition)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,
			      DIRAC_COUNT(LineVertex::mColor, float),
			      GL_FLOAT,
			      GL_FALSE,
			      sizeof(LineVertex),
			      (void*)(offsetof(LineVertex, mColor)));
	glEnableVertexAttribArray(1);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void BatchLineRenderer::update(EntityID tCameraID)
{
	mShader -> bind();
	glBindVertexArray(mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	
	auto lCameraTransform = gManager.getComponent<Transform>(tCameraID);
	auto lCameraView = gManager.getComponent<View>(tCameraID);
	
	Matrix lCameraAttitudeT = transpose(lCameraTransform.mAttitude);

	// Camera view uniforms
	mShader -> setUniform("uCameraDeltax", lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", lCameraView.mAspectRatio);

	// Pointer to Vertex buffer data
	LineVertex* lMapBuffer = (LineVertex*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));


	LineVertex lLineVertex;

	unsigned int lCurrentVertex = 0;

	for (EntityID entity: mEntities)
	{	

		if (lCurrentVertex >= Constants::MAX_VERTICES_BATCH)
		{
			break;
		}
		// Retrieve Line data
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

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glLineWidth(mLineWidth);
	glDrawArrays(GL_LINES, 0, lCurrentVertex);
}


void BatchLineRenderer::destroy(void)
{
	glDeleteVertexArrays(1, &mVertexArrayID);
	glDeleteBuffers(1, &mVertexBufferID);
	
	delete mShader;
}



};
