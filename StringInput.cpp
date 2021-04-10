#include "StringInput.h"

#include <fstream>
#include <iostream>


std::string readShader(const std::string& shaderAddress){

	std::ifstream file(shaderAddress);

	std::string shader;
	std::string line;

	if (not file.is_open()){

		std::cout << "\t...troubles finding the shader source at: " << shaderAddress << "..." << std::endl;
	}
	else{

		while (getline(file, line)){

			shader.append(line + "\n");
		}
	}
	file.close();

	return shader;
}


std::vector<std::string> getUniforms(const std::string& shaderAddress){

	std::ifstream file(shaderAddress);

	std::string line;
	std::vector<std::string> uniforms;
	std::vector<std::string> words;

	if (not file.is_open()){

		std::cout << "\t...troubles finding the shader source at: " << shaderAddress << "..." << std::endl;
	}
	else{
		
		while(getline(file, line)){

			if (line.size() > 0){
				
				words = splitLine(line);

				if (words[0] == "uniform"){

					uniforms.push_back(words.back().substr(0, words.back().size() - 1));
				}
			}
		}
	}
	return uniforms;
}


std::vector<std::string> splitLine(const std::string& line){
        /* splits the line into word */

        std::string delimiter = " ";
        std::vector<std::string> words;
        std::string word;

        size_t startPos = 0;
        size_t endPos = line.find(delimiter);
        words.push_back(line.substr(startPos, endPos - startPos));

        while (endPos != std::string::npos){

                startPos = endPos + 1;
                endPos = line.find(delimiter, startPos);
                words.push_back(line.substr(startPos, endPos - startPos));
        }

        return words;
}


void parseDirac(const std::string& address, std::vector<float>& vertexData, std::vector<unsigned int>& indexData){

	std::ifstream file(address);
	
	if (not file.is_open()){

		std::cout << "\t...troubles loading model at " << address << std::endl;
	}


	std::string line;

	while (getline(file, line)){
		
		if (line.size() > 0){

			std::vector<std::string> words = splitLine(line);

			if (words[0] == "v"){

				for (int i = 1; i < words.size(); i++){

					vertexData.push_back(stof(words[i]));
				}
			}
			else if (words[0] == "i"){
				
				for (int i = 1; i < words.size(); i++){
				
					indexData.push_back(static_cast<unsigned>(stoi(words[i])));
				}
			}
		}
	}
	file.close();
}


