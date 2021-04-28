#include "DynamicBatchRenderer.h"

#include <GL/glew.h>
#include <cstddef>		// offsetof
#include <cstring>		// memcpy

#include "Shader.h"
#include "Manager.h"
#include "DiracMacros.h"


extern Dirac::Manager gManager;


namespace Dirac
{


void DynamicBatchRenderer::init(void)
{
	// Shader
	mShader = new Shader("./resources/shaders/batchVertex.shader",
			     "./resources/shaders/batchFragment.shader");
	
	// Generate and bind buffers
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

	// Allocate space in the GPU
	glBufferData(GL_ARRAY_BUFFER,
		     Constants::MAX_VERTICES_BATCH * sizeof(Vertex),
		     nullptr,
		     GL_DYNAMIC_DRAW);

	// Specify data layout
	glVertexAttribPointer(0,
			      DIRAC_COUNT(Vertex::mPosition, float),
			      GL_FLOAT,
			      GL_FALSE,
			      sizeof(Vertex),
			      (void*)(offsetof(Vertex, mPosition)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,
			      DIRAC_COUNT(Vertex::mNormal, float),
			      GL_FLOAT,
			      GL_FALSE,
			      sizeof(Vertex),
			      (void*)(offsetof(Vertex, mNormal)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2,
			      DIRAC_COUNT(Vertex::mColor, float),
			      GL_FLOAT,
			      GL_FALSE,
			      sizeof(Vertex),
			      (void*)(offsetof(Vertex, mColor)));
	glEnableVertexAttribArray(2);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void DynamicBatchRenderer::update(EntityID tCameraID)
{
	// update uniform + draw call
	mShader -> bind();
	glBindVertexArray(mVertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

	auto lCameraTransform 	= gManager.getComponent<Transform>(tCameraID);
	auto lCameraView 	= gManager.getComponent<View>(tCameraID);

	// camera view uniforms
	mShader -> setUniform("uCameraDeltax", 		lCameraView.mDeltax);
	mShader -> setUniform("uCameraDeltaz", 		lCameraView.mDeltaz);
	mShader -> setUniform("uCameraNear", 		lCameraView.mNearPlane);
	mShader -> setUniform("uCameraAspectRatio", 	lCameraView.mAspectRatio);


	Vertex* lMapBuffer = (Vertex*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

	Vertex lVertex;

	unsigned int lCurrentVertex = 0;
	
	Matrix lCameraAttitudeT = transpose(lCameraTransform.mAttitude);
	
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

			memcpy((lMapBuffer + lCurrentVertex), &lVertex, sizeof(Vertex));

			lCurrentVertex ++;
		}

	}


	glUnmapBuffer(GL_ARRAY_BUFFER);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(Vertex) * lCurrentVertex);

}


void DynamicBatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);

	delete mShader;
}


};
