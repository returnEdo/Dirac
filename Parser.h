#pragma once

#include <vector>
#include <string>

namespace Dirac
{

using Words = std::vector<std::string>;

// converts the contents of a file to a string
std::string convertToString(const std::string& tAddress);

// split the content of a line
Words splitLine(const std::string& tLine, const std::string& tDelimiter);

Words tokenize(const std::string& tLine);

// finds the uniforms in the shaders
Words findUniforms(const std::string& tAddress);

};
