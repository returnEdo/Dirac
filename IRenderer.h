#pragma once

#include <vector>

#include "Entity.h"
#include "Shader.h"

namespace Dirac
{


struct DataLayout
{
	unsigned int 	mCount		= 0;	
	unsigned int	mType		= GL_FLOAT;
	unsigned int 	mNormalize 	= GL_FALSE;
	unsigned int	mOffset		= 0;
};


void enableAttributes(std::vector<DataLayout> tDataLayout);


class IRenderer
{
	protected:

	unsigned int mVertexArrayID = 0;
	unsigned int mVertexBufferID = 0;
	unsigned int mIndexBufferID = 0;

	Shader* mShader = nullptr;

	public:
	
	virtual ~IRenderer(void) {};

	virtual void init(void) = 0;
	virtual void update(EntityID tCameraID) = 0;
	virtual void destroy(void) = 0;
};

};
