#include <iostream>
#include "Vector.h"
#include "Matrix.h"


using namespace std;


int main(){
	
	Matrix mat1;
	
	Vector vec1 = Vector(1.0, 1.0, 1.0);
	Vector vec2 = Vector(.0, 1.0, 1.0);
	Vector vec3 = Vector(.0, .0, 1.0);
	
	Matrix mat4 = Matrix(vec1, vec2, vec3);
	Matrix mat5 = inv(mat4);
	
	
	
	cout << mat4 << endl;
	cout << mat5 << endl;
	cout << (mat5 * mat4) << endl;

	
	return 0;
}

