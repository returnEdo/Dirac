#include <array>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
#include "Vector.h"


struct Buffers{

	std::vector<std::vector<int> > indexBuffer;
	std::vector<std::vector<int> > uvBuffer;
	std::vector<std::vector<int> > normalBuffer;
};




void cautiosInsertionDouble(std::string& word, std::vector<double>& vec){
	/* Attentive insertion  */

	try{
		vec.push_back(std::stod(word));
	}
	catch (std::invalid_argument){

	}
}



void cautiosInsertionInt(std::string& word, std::vector<int>& vec){

	if (word[0] != 'f'){
		
		std::string divider = "/";

		try{

			vec.push_back(std::stoi(word.substr(0, word.find(divider))));
		}
		catch (std::invalid_argument)	{ }
	}
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
			std::string remaingLine = currentLine.substr(endPos + 1, std::string::npos);
			

			if (keyword  == vertexKey){
				/* parsing vertices coordinates  */
				
				std::vector<std::string> temp = splitByDelimiter(remaingLine, space);

				xM.push_back(convertToVector(temp));
			}
			else if (keyword == textureKey){
				/* uv texture coordinates  */

			}
			else if (keyword == normalKey){
				/* vertex normals  */

				std::vector<std::string> temp = splitByDelimiter(remaingLine, space);

				n.push_back(convertToVector(temp));
			}
			else if (keyword == buffersKey){

				std::vector<std::string> temp = splitByDelimiter(remaingLine, space);
				
				addToTheBuffers(buffer, temp);
			}
		}
	}
}





int main(){
	

	Buffers buff;
	std::string address = "cube.obj";
	
	std::vector<Vector> xM;
	std::vector<Vector> normals;

	getObject(address, xM, normals, buff);
	
	for (auto const& x: buff.uvBuffer){

		std::cout << x[0] << " " << x[1] << " " << x[2] << std::endl;
	}

	return 0;
}
