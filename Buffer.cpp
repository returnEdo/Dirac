#include "Buffer.h"




namespace Dirac
{

namespace Graphics
{

Buffer::Buffer(unsigned int tTarget):	mTarget(tTarget)
{
	glGenBuffers(1, &mID);
	bind();
}


Buffer::~Buffer(void)
{	
	glDeleteBuffers(1, &mID);
}


void Buffer::bind(bool tBind)
{
	glBindBuffer(mTarget, (tBind? mID: 0));
}


void Buffer::allocate(unsigned int tSize, unsigned int tMode)
{	
	glBufferData(mTarget, tSize, nullptr, tMode);
}

void Buffer::unmapBuffer(void)
{
	glUnmapBuffer(mTarget);
}

};


};
