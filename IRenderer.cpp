#include "IRenderer.h"

#include "DiracMacros.h"

#include <GL/glew.h>

namespace Dirac
{


void enableAttributes(std::vector<DataLayout> tDataLayout)
{
	unsigned int lStride = 0;

	for (auto& dataLayout: tDataLayout)	
	{
		dataLayout.mOffset = lStride;
		lStride += dataLayout.mCount * sizeof(float);
	}

	for (int i = 0; i < tDataLayout.size(); i++)
	{
		DataLayout lDataLayout = tDataLayout[i];
		glVertexAttribPointer(i,
				      lDataLayout.mCount,
				      lDataLayout.mType,
				      lDataLayout.mNormalize,
				      lStride,
				      (void*)(lDataLayout.mOffset));

		glEnableVertexAttribArray(i);
	}

}


};
