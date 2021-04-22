#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include "Vector2.h"
#include "Vector.h"
#include "Matrix.h"



namespace Dirac
{


enum class ShaderType
{
	VERTEX,
	FRAGMENT
};	

unsigned int getShaderID(const std::string tShaderAddress, ShaderType tType);


class Shader
{
	private:

	unsigned int mID { };
	std::unordered_map<std::string, int> mUniformLocations;

	// buffers
	float mVectorBuffer[3];
	float mMatrixBuffer[9];
	
	public:

	Shader(const std::string& tVertexShaderAddress,
	       const std::string& tFragmentShaderAddress);

	~Shader(void);

	void bind(void);
	void unbind(void);


	void setUniform(const std::string& tUniform, float newValue);
	void setUniform(const std::string& tUniform, const Vector2& newValue);
	void setUniform(const std::string& tUniform, const Vector& newValue);
	void setUniform(const std::string& tUniform, const Matrix& newValue);

};


};
