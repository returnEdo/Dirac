#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include "Vector2.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"



namespace Dirac
{

namespace Graphics
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

	public:

	Shader(const std::string& tVertexShaderAddress,
	       const std::string& tFragmentShaderAddress);

	~Shader(void);

	void bind(void);
	void unbind(void);

	inline unsigned int getID(void)	{ return mID; }

	void setUniform(const std::string& tUniform, float newValue);
	void setUniform(const std::string& tUniform, Vector2& newValue);
	void setUniform(const std::string& tUniform, Vector& newValue);
	void setUniform(const std::string& tUniform, Matrix& newValue);

};

};

};
