#include "Texture.hpp"

#include <GL/glew.h>

#include "DiracMacros.hpp"
#include "stb_image.h"



namespace Dirac
{

namespace Graphics
{

unsigned int Texture::sTextureCounter = 0;

Texture::Texture(const std::string& tTextureAddress)
{

	DIRAC_ASSERT(Texture::sTextureCounter < 16, "Cannot generate other textures!!");

	mOpenGLTextureIndex = GL_TEXTURE0 + Texture::sTextureCounter;	
	Texture::sTextureCounter ++;

	glGenTextures(1, &mTextureID);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	
	unsigned char *lTextureData = stbi_load(tTextureAddress.c_str(), &mWidth, &mHeight, &mChannels, 0);
	
	DIRAC_ASSERT((lTextureData != nullptr), "Failed to load texture!!");

	unsigned int DATA_TYPE = (mChannels == 3? GL_RGB: GL_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, DATA_TYPE, mWidth, mHeight, 0, DATA_TYPE, GL_UNSIGNED_BYTE, lTextureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(lTextureData);

}


Texture::~Texture(void)
{
	glDeleteTextures(1, &mTextureID);
}



void Texture::bind(void)
{
	glActiveTexture(mOpenGLTextureIndex);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}





};

};
