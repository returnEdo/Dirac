#pragma once

#include <vector>

#include "Entity.h"
#include "System.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "DiracConstants.h"
#include "RenderingComponents.h"


namespace Dirac
{

/*
SIGNATURE:
- Transform
- Color
- Model
*/

class DynamicBatchRenderer: public ISystem
{
	private:

	Graphics::Shader*	mShader		{ nullptr };
	Graphics::Buffer*	mVertexBuffer	{ nullptr };
	Graphics::VertexArray*	mVertexArray	{ nullptr };

	public:

	void init(void);
	void update(EntityID tCameraID);
	void destroy(void);
};


};
