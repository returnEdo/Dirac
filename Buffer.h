#pragma once

#include <GL/glew.h>
#include "DiracMacros.h"


namespace Dirac
{

namespace Graphics
{

class Buffer
{
	private:

	unsigned int mID	{ 0 };
	unsigned int mTarget	{ 0 };

	public:

	Buffer(unsigned int tTarget);
	~Buffer(void);

	void bind(bool tBind = true);
	void allocate(unsigned int tSize, unsigned int tMode = GL_DYNAMIC_DRAW);

	template <typename T>
	T* getBuffer(unsigned int tMode = GL_WRITE_ONLY)
	{
		T* lBufferData = (T*)(glMapBuffer(mTarget, tMode));

		DIRAC_ASSERT((lBufferData != nullptr), "Could not acces the GPU!!");
		
		return lBufferData;
	}

	void unmapBuffer(void);
};


};


};
