#pragma once

#include <string>
#include <vector>

std::string readShader(const std::string& shaderAddress);
std::vector<std::string> getUniforms(const std::string& shaderAddress);
std::vector<std::string> splitLine(const std::string& line);
void parseDirac(const std::string& address, std::vector<float>& vertexData, std::vector<unsigned int>& indexData);

