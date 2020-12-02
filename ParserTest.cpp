#include <iostream>
#include "OBJParser.h"
#include "Vector.h"
#include <vector>
#include <string>


using namespace std;


int main(){

	vector<vector<int> > indexBuffer;
	vector<Vector> xM;

	string address = "cube.obj";

	getObject(address, xM, indexBuffer);	


	for (auto const& indx: indexBuffer){

		cout << indx[0] << indx[1] << indx[2] << endl;
	}
	for (Vector const& Vertex: xM){

		cout << Vertex << endl;
	}

	return 0; 
}
