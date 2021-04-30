#pragma once

#include <string>


namespace Dirac
{

namespace Graphics
{

class Texture
{
	private:

	unsigned int mTextureID			{ 0 };

	unsigned int mOpenGLTextureIndex	{ 0 };
	static unsigned int sTextureCounter;

	int mWidth				{ 0 };
	int mHeight				{ 0 };
	int mChannels				{ 0 };

	public:

	Texture(const std::string& tTextureAddress);
	~Texture(void);

	void bind(void);

	inline float getWidth(void) 	const { return (static_cast<float>(mWidth)); }
	inline float getHeight(void) 	const { return (static_cast<float>(mHeight)); }
};


};


};
