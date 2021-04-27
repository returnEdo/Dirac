#include "MeshRenderer.h"

#include "Manager.h"
#include "RenderingComponents.h"
#include "DiracMacros.h"


extern Dirac::Manager gManager;

namespace Dirac
{



namespace Meshes
{
	float lTriangleMesh[] = 
	{
		-.5f, -.5f, .0f, .0f, .0f, 1.0f,
		.5f, -.5f, .0f, .0f, .0f, 1.0f,
		.0f, .5f, .0f, .0f, .0f, 1.0f
	};

	float lCubeMesh[] = 
	{
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
						 
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
						 
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
						 
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
						 
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
						 
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};
};

	


void MeshRenderer::init(void)
{	
	// Shader
	mShader = new Shader("resources/shaders/bareboneVertexShader.shader",
			     "resources/shaders/bareboneFragmentShader.shader");
		
	// Vertex array and vertex buffer
	// 1) Generation & binding
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);

	// 2) Data + data format
	glBufferData(GL_ARRAY_BUFFER, sizeof(Meshes::lCubeMesh), Meshes::lCubeMesh, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, sizeof(VertexDataLayout::mPosition) / sizeof(float),
	//		      GL_FLOAT, GL_FALSE,
	//		      sizeof(VertexDataLayout),
	//		      (void*)0);
	//glEnableVertexAttribArray(0);
	//
	//glVertexAttribPointer(1, sizeof(VertexDataLayout::mNormal) / sizeof(float),
	//		      GL_FLOAT, GL_FALSE,
	//		      sizeof(VertexDataLayout),
	//		      (void*)(sizeof(VertexDataLayout::mPosition)));
	//glEnableVertexAttribArray(1);

	Dirac::enableAttributes({{3, GL_FLOAT, GL_FALSE},
				 {3, GL_FLOAT, GL_FALSE}});

	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
        
}



void MeshRenderer::update(EntityID tCameraID)
{
	// update uniform + draw call
	mShader -> bind();
	glBindVertexArray(mVertexArrayID);

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


	for (auto lEntity: mEntities)
	{
		auto lEntityTransform = gManager.getComponent<Transform>(lEntity);
		auto lEntityColor = gManager.getComponent<Color>(lEntity);

		// entity transform uniforms
		mShader -> setUniform("uEntityPosition", lEntityTransform.mPosition);
		mShader -> setUniform("uEntityAttitude", lEntityTransform.mAttitude);
		mShader -> setUniform("uEntityShear", lEntityTransform.mShear);
	
		// entity color uniforms
		mShader -> setUniform("uEntityAlpha", lEntityColor.mAlpha);
		mShader -> setUniform("uEntityColor", lEntityColor.mColor);
		
		glDrawArrays(GL_TRIANGLES, 0, sizeof(Meshes::lCubeMesh) / sizeof(VertexDataLayout));
	}
}


void MeshRenderer::destroy(void)
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);

	delete mShader;
}



};
