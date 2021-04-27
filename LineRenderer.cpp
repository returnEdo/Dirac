#include "LineRenderer.h"

#include <GL/glew.h>

#include "DiracConstants.h"
#include "Manager.h"
#include "RenderingComponents.h"



extern Dirac::Manager gManager;

namespace Dirac
{

float outer[6] =
{
	3.0f, 3.0f, 3.0f,
	.0f, .0f, .0f
};


void LineRenderer::init(void)
{
	
	// Compile shader
	mShader = new Shader("./resources/shaders/lineVertex.shader",
			     "./resources/shaders/lineFragment.shader");

	// Generate buffers
	glGenVertexArrays(1, &mVertexArrayID);
	glGenBuffers(1, &mVertexBufferID);
	
	// Fill with data
	glBindVertexArray(mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(ExtremumLayout) * Constants::MAX_LINES, NULL, GL_DYNAMIC_DRAW);

	// Vertex data format
	Dirac::enableAttributes({{3, GL_FLOAT, GL_FALSE}});

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void LineRenderer::update(EntityID tCameraID)
{
	mShader -> bind();
	glBindVertexArray(mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	
	auto lCameraTransform = gManager.getComponent<Transform>(tCameraID);
	auto lCameraView = gManager.getComponent<View>(tCameraID);

	// camera transform uniforms
	mShader -> setUniform("uCameraPosition", lCameraTransform.mPosition);
	mShader -> setUniform("uCameraAttitude", lCameraTransform.mAttitude);

	// camera view uniforms
	mShader -> setUniform("uCameraDeltax", lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", lCameraView.mAspectRatio);

	

	int lIndex { 0 };
	for (EntityID entity: mEntities)
	{
		Line& lLine = gManager.getComponent<Line>(entity);
		
		glBufferSubData(GL_ARRAY_BUFFER,
				lIndex * 2 * sizeof(ExtremumLayout),
				2 * sizeof(ExtremumLayout),
				&lLine);
		lIndex ++;
	}

	glLineWidth(1.0f);
	glDrawArrays(GL_LINES, 0, 2 * sizeof(ExtremumLayout) / sizeof(float) * lIndex);
}


void LineRenderer::destroy(void)
{
	glDeleteVertexArrays(1, &mVertexArrayID);
	glDeleteBuffers(1, &mVertexBufferID);
	
	delete mShader;
}



};
