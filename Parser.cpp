#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
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

			vec.push_back(std::stoi(word.substr(0, word.find(divider))));
		}
		catch (std::invalid_argument)	{ }
	}
}


int main(){

	std::vector<Vector> ModelVertices;	
	std::vector<std::vector<int> > indexBuffer;
	std::string address = "monkey.obj"; 


	std::ifstream MyFile(address);

	if (MyFile.is_open()){

		std::string currentLine;

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

				std::cout << vec[0] << "\t"<< vec[1] << "\t" << vec[2] << std::endl;

				vec.clear();
			}
		}	

	}
	std::cout << ModelVertices.size() << std::endl;

	for (auto const& Vertex: ModelVertices){

		std::cout << Vertex << std::endl;
	}

}
