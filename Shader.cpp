#include "Shader.h"

#include <iostream>
#include <fstream>

#include "StringInput.h"
#include "DiracConstants.h"



unsigned int createShader(const std::string& shaderAddress, const SHADER_TYPE& shaderType){

	std::string shader = readShader(shaderAddress);
	const char* rawShader = shader.c_str();

	unsigned int shaderID = glCreateShader((shaderType == SHADER_TYPE::VERTEX? GL_VERTEX_SHADER: GL_FRAGMENT_SHADER));
	glShaderSource(shaderID, 1, &rawShader, NULL);
	glCompileShader(shaderID);

	if (Constants::VERBOSE){
		/* error checking */
		int roger;
		char info[512];
		
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &roger);
		if (not roger){

			glGetShaderInfoLog(shaderID, 512, NULL, info);
			std::cout << "\t...troubles compiling " << (shaderType == SHADER_TYPE::VERTEX? "VERTEX": "FRAGMENT") << " shader ..." << std::endl;
			std::cout << info << std::endl;
		}
	}

	return shaderID;
}



Shader::Shader(const std::string& vertexShaderAddress, const std::string& fragmentShaderAddress){
	/* links the shaders into a program */

	unsigned int vertexHandle = createShader(vertexShaderAddress, SHADER_TYPE::VERTEX);
	unsigned int fragmentHandle = createShader(fragmentShaderAddress, SHADER_TYPE::FRAGMENT);

	id = glCreateProgram();
	glAttachShader(id, vertexHandle);
	glAttachShader(id, fragmentHandle);
	glLinkProgram(id);

	if (Constants::VERBOSE){
		/* checks for errors in the linking process */
		int roger;
		char info[512];
		glGetShaderiv(id, GL_LINK_STATUS, &roger);
		if (not roger){
			
			glGetProgramInfoLog(id, 512, NULL, info);
			std::cout << "\t...troubles in linking shaders to a program ..." << std::endl;
			std::cout << info << std::endl;
		}
	}

	glDeleteShader(vertexHandle);
	glDeleteShader(fragmentHandle);

	/* find the id for each uniform found in the shaders */
	std::vector<std::string> vertexUniforms = getUniforms(vertexShaderAddress);
	std::vector<std::string> fragmentUniforms = getUniforms(fragmentShaderAddress);

	for (const std::string& uniform: vertexUniforms){
		
		uniformLocations[uniform] = glGetUniformLocation(id, uniform.c_str());
	}
	for (const std::string& uniform: fragmentUniforms){
		
		uniformLocations[uniform] = glGetUniformLocation(id, uniform.c_str());
	}
}


Shader::~Shader(void){

	glDeleteProgram(id);
}

void Shader::bind(void) const{

	glUseProgram(id);
}

void Shader::unbind(void) const{

	glUseProgram(0);
}


void Shader::setUniform(const std::string& uniform, float newValue){

	glUniform1f(uniformLocations[uniform], newValue);
}


void Shader::setUniform(const std::string& uniform, const Vector2& newValue){

	newValue.getRaw(vectorBuffer);

	glUniform2fv(uniformLocations[uniform], 1, vectorBuffer);
}


void Shader::setUniform(const std::string& uniform, const Vector& newValue){

	newValue.getRaw(vectorBuffer);

	glUniform3fv(uniformLocations[uniform], 1, vectorBuffer);
}



void Shader::setUniform(const std::string& uniform, const Matrix& newValue){

	newValue.getColumnMajorOrder(matrixBuffer);

	glUniformMatrix3fv(uniformLocations[uniform], 1, GL_FALSE, matrixBuffer);
}





