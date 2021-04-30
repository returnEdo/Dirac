#pragma once

#include "Entity.hpp"
#include "System.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "RenderingComponents.hpp"
#include "Memory/Unique.hpp"


namespace Dirac
{

/*
SIGNATURE
-Line	
*/


class BatchLineRenderer: public ISystem
{
	private:

	Memory::Unique<Graphics::Shader>	mShader;
	Memory::Unique<Graphics::Buffer>	mVertexBuffer;
	Memory::Unique<Graphics::VertexArray>	mVertexArray;
	
	float mLineWidth = 1.0f;

	public:

	void init(void);
	void update(EntityID tCameraID);

	inline void setLineWidth(float tLineWidth) 	{ mLineWidth = tLineWidth; } 
};


};
