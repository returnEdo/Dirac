#pragma once


#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include "Vector.h"



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

			vec.push_back(std::stoi(word.substr(0, word.find(divider))) - 1);
		}
		catch (std::invalid_argument)	{ }
	}
}


bool typeCheck(const std::string& address){

	int n = address.length();
	size_t dotPosition = address.find(".");

	if (address.substr(dotPosition + 1, n - dotPosition) == "obj"){ return true; }

	return false;
}


void getObject(const std::string& address, std::vector<Vector>& ModelVertices,
		std::vector<std::vector<int> >& indexBuffer){
	/* Parses model vertices and index buffer from an obj file  */
	
	if (not(typeCheck(address))) { return; }


	std::string token = " ";

	std::ifstream MyFile(address);

	if (MyFile.is_open()){

		std::string currentLine;
		
		/* scans alla the lines  */
		while(getline(MyFile, currentLine)){
			
			if (currentLine.substr(0, 2) == "v "){
				/* The line is vertex data  */
				
				std::vector<double> vec;
								
				std::string token = " ";

				size_t startPos = 0;
				size_t endPos = currentLine.find(token); 

				while (endPos != std::string::npos){			// as long as there's the token

					std::string word = currentLine.substr(startPos, endPos - startPos); // works with increments
					

					cautiosInsertionDouble(word, vec);					

					startPos = endPos + token.length();
					endPos = currentLine.find(token, startPos);
				}

				std::string word = currentLine.substr(startPos, endPos);
				
				cautiosInsertionDouble(word, vec);

				assert(vec.size() == 3);
				
				ModelVertices.push_back(Vector(vec));
				vec.clear();



			}
			else if (currentLine.substr(0, 2) == "f "){

				std::vector<int> vec;

				std::string token = " ";

				size_t startPos = 0;
				size_t endPos = currentLine.find(token);

				while (endPos != std::string::npos){

					std::string word = currentLine.substr(startPos, endPos - startPos);

					cautiosInsertionInt(word, vec);

					startPos = endPos + token.length();
					endPos = currentLine.find(token, startPos);
				}

				std::string word = currentLine.substr(startPos, endPos);
				cautiosInsertionInt(word, vec);

				assert(vec.size() == 3);

				indexBuffer.push_back(vec);

				vec.clear();
			}
		}	

	}

}
