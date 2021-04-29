#pragma once

#include "Entity.h"
#include "System.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "RenderingComponents.h"


namespace Dirac
{

/*
SIGNATURE
-Line	
*/


class BatchLineRenderer: public ISystem
{
	private:

	Graphics::Shader*	mShader		{ nullptr };
	Graphics::Buffer*	mVertexBuffer	{ nullptr };
	Graphics::VertexArray*	mVertexArray	{ nullptr };
	
	float mLineWidth = 1.0f;

	public:

	void init(void);
	void update(EntityID tCameraID);
	void destroy(void);

	inline void setLineWidth(float tLineWidth) 	{ mLineWidth = tLineWidth; } 
};


};
