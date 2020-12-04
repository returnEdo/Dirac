#pragma once

#include <array>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
#include "Vector.h"
#include "Vector2.h"
#include "Object.h"

#ifndef BUFFERS_STRUCT
#define BUFFERS_STRUCT
struct Buffers{

	vector<vector<int> > indexBuffer;
	vector<vector<int> > uvBuffer;
	vector<vector<int> > normalBuffer;
};
#endif



Vector2 convertToVector2(const std::vector<std::string>& vecs){

	try{
		Vector2 val = Vector2();


		val.x = std::stod(vecs[0]);
		val.y = std::stod(vecs[1]);

		return val;
	}
	catch (std::invalid_argument){}
}


Vector convertToVector(const std::vector<std::string>& vecs){

	try{
		Vector val = Vector();


		val.x = std::stod(vecs[0]);
		val.y = std::stod(vecs[1]);
		val.z = std::stod(vecs[2]);

		return val;
	}
	catch (std::invalid_argument){}
}


std::vector<std::string>  splitByDelimiter(std::string& word, std::string delimiter){
	/* splits a string using the deliimiter  */
	
	std::vector<std::string> dividedString;
	std::string val;

	size_t n = delimiter.length();

	size_t startPos = 0;
	size_t endPos = word.find(delimiter, startPos);

	while (endPos != std::string::npos){
		
		val = word.substr(startPos, endPos - startPos);

		dividedString.push_back(val);

		startPos = endPos + n;	
		endPos = word.find(delimiter, startPos);
	}

	dividedString.push_back(word.substr(startPos, std::string::npos));	// till the end
	
	return dividedString;
}


void addToTheBuffers(Buffers& buff, std::vector<std::string>& splittedLine){

	std::vector<int> tempib;
	std::vector<int> tempuv;
	std::vector<int> tempn;
	
	for (std::string& str: splittedLine){

		std::vector<std::string> values = splitByDelimiter(str, "/");

		tempib.push_back(std::stoi(values[0]) - 1);
		tempuv.push_back(std::stoi(values[1]) - 1);
		tempn.push_back(std::stoi(values[2]) - 1);
	}

	buff.indexBuffer.push_back(tempib);
	buff.uvBuffer.push_back(tempuv);
	buff.normalBuffer.push_back(tempn);
}


void getObject(const std::string& address,
	       std::vector<Vector>& xM,
       	       std::vector<Vector>& n,
	       std::vector<Vector2>& uvs,
	       Buffers& buffer){
	/* complete .obj parser  */

	std::string space = " ";
	std::string vertexKey = "v ";
	std::string textureKey = "vt ";
	std::string normalKey = "vn ";
	std::string buffersKey = "f ";

	std::ifstream fl(address);

	if (fl.is_open()){			// checks the file has been correctly opened

		std::string currentLine;

		while(getline(fl, currentLine)){
			
			size_t endPos = currentLine.find(space);

			std::string keyword = currentLine.substr(0, endPos + 1);
			std::string remainingLine = currentLine.substr(endPos + 1, std::string::npos);
			std::vector<std::string> temp = splitByDelimiter(remainingLine, space);

			if (keyword  == vertexKey){
				/* parsing vertices coordinates  */
				
				xM.push_back(convertToVector(temp));
			}
			else if (keyword == textureKey){
				/* uv texture coordinates  */

				uvs.push_back(convertToVector2(temp));
			}
			else if (keyword == normalKey){
				/* vertex normals  */

				n.push_back(convertToVector(temp));
			}
			else if (keyword == buffersKey){

				addToTheBuffers(buffer, temp);
			}
		}
	}
}


