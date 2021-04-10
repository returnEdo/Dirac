#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>

#include "Vector2.h"
#include "Vector.h"
#include "Matrix.h"


enum class SHADER_TYPE{

	VERTEX,
	FRAGMENT,
	COMPUTE
};


unsigned int createShader(const std::string& shaderAddress, const SHADER_TYPE& shaderType);


class Shader{

	private:

	unsigned int id;	
	std::unordered_map<std::string, int> uniformLocations;

	/* buffers for uniforms */
	float vectorBuffer[3];
	float matrixBuffer[9];

	public:

	Shader(const std::string& vertexShaderAddress, const std::string& fragmentShaderAddr);
	~Shader(void);
	
	/* uniforms */
	void setUniform(const std::string& uniform, float newValue);
	void setUniform(const std::string& uniform, const Vector2& newValue);
	void setUniform(const std::string& uniform, const Vector& newValue);
	void setUniform(const std::string& uniform, const Matrix& newValue);

	
	/* binding */
	void bind(void) const;
	void unbind(void) const;

};
