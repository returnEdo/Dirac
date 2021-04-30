#include "VertexArray.hpp"

#include <GL/glew.h>


namespace Dirac
{

namespace Graphics
{

VertexArray::VertexArray(void): mCurrentAttribute(0)
{
	glGenVertexArrays(1, &mID);
	bind();
}

VertexArray::~VertexArray(void)
{
	glDeleteVertexArrays(1, &mID);
}

void VertexArray::bind(bool tBind)
{
	glBindVertexArray((tBind? mID: 0));
}

void VertexArray::addAttribute(Attribute tAttribute)
{
	glVertexAttribPointer(mCurrentAttribute,
			      tAttribute.mCount,
			      tAttribute.mGLType,
			      GL_FALSE,
			      tAttribute.mStride,
			      (void*)(tAttribute.mOffset));
	glEnableVertexAttribArray(mCurrentAttribute);

	mCurrentAttribute ++;
}


};


};
