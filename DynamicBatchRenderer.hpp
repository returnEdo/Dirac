#pragma once

#include <vector>

#include "Entity.hpp"
#include "System.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "DiracConstants.hpp"
#include "RenderingComponents.hpp"
#include "Memory/Unique.hpp"


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

	Memory::Unique<Graphics::Shader>	mShader;
	Memory::Unique<Graphics::Buffer>	mVertexBuffer;
	Memory::Unique<Graphics::VertexArray>	mVertexArray;

	public:

	void init(void);
	void update(EntityID tCameraID);
};


};
