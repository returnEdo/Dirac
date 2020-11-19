#include <iostream>
#include "Vector.h"
#include "Matrix.h"


using namespace std;


int main(){
	
	Matrix mat1;
	
	//~ Vector r1 = Vector(1, 2, 3);
	//~ Vector r2 = Vector(4, 5, 6);
	//~ Vector r3 = Vector(7, 8, 9);
	
	
	//~ Matrix mat2 = Matrix(r1, r2, r3);
	
	//~ cout << mat2 << endl;
	//~ cout << mat1 << endl;
	
	Matrix mat3 = mat1 * 2.0;
	
	cout << mat3 << endl;
	
	return 0;
}

