#include "Shader.hpp"


#include "DiracMacros.hpp"
#include "Parser.hpp"


namespace Dirac
{

namespace Graphics
{

unsigned int getShaderID(const std::string tShaderAddress, ShaderType tType)
{
	unsigned int lID = glCreateShader((tType == ShaderType::VERTEX? GL_VERTEX_SHADER: GL_FRAGMENT_SHADER));
	
	// convert source to char
	std::string lShaderString = Dirac::convertToString(tShaderAddress);

	const char* lShaderChar = lShaderString.c_str();

	glShaderSource(lID, 1, &lShaderChar, NULL);
	glCompileShader(lID);

	int lPassed;
	glGetShaderiv(lID, GL_COMPILE_STATUS, &lPassed);

	if (not lPassed)
	{
		char lErrorInfo[512];
		glGetShaderInfoLog(lID, 512, NULL, lErrorInfo);
		
		std::string lShaderType = (tType == ShaderType::VERTEX? "vertex ": "fragment ");
		DIRAC_ASSERT(false, "Error in " + lShaderType + "shader!!" + "\n\t" + lErrorInfo);
	}

	return lID; 
}



Shader::Shader(const std::string& tVertexShaderAddress,
	       const std::string& tFragmentShaderAddress)
{
	// create shaders
	unsigned int lVertexID = getShaderID(tVertexShaderAddress, ShaderType::VERTEX);
	unsigned int lFragmentID = getShaderID(tFragmentShaderAddress, ShaderType::FRAGMENT);

	
	// assemble program
	mID = glCreateProgram();

	glAttachShader(mID,lVertexID);
	glAttachShader(mID,lFragmentID);
	glLinkProgram(mID);
	
	int lPassed;
	glGetShaderiv(mID, GL_LINK_STATUS, &lPassed);
	
	DIRAC_ASSERT(lPassed, "Could not link shaders into a program!!");
	
	// delete shaders
	glDeleteShader(lVertexID);
	glDeleteShader(lFragmentID);

	// Register uniforms in the dictionary
	Dirac::Words lVertexUniforms 	= findUniforms(tVertexShaderAddress);
	Dirac::Words lFragmentUniforms 	= findUniforms(tFragmentShaderAddress);

	for (auto lUniformName: lVertexUniforms)
	{	
		mUniformLocations[lUniformName] = glGetUniformLocation(mID, lUniformName.c_str());
	}

	for (auto lUniformName: lFragmentUniforms)
	{	
		mUniformLocations[lUniformName] = glGetUniformLocation(mID, lUniformName.c_str());
	}
}


Shader::~Shader(void)
{
	glDeleteProgram(mID);
}


void Shader::bind(void)
{
	glUseProgram(mID);
}


void Shader::unbind(void)
{
	glUseProgram(0);
}


void Shader::setUniform(const std::string& tUniform, float newValue){

	glUniform1f(mUniformLocations[tUniform], newValue);
}


void Shader::setUniform(const std::string& tUniform, Math::vec2& tVec2){

	glUniform2fv(mUniformLocations[tUniform], 1, (float*)(&tVec2));
}

void Shader::setUniform(const std::string& tUniform, Math::vec3& newValue){

	glUniform3fv(mUniformLocations[tUniform], 1, (float*)(&newValue));
}


void Shader::setUniform(const std::string& tUniform, Math::mat3& tMatrix){

	glUniformMatrix3fv(mUniformLocations[tUniform], 1, GL_FALSE, (float*)(&tMatrix));
}

};

};
