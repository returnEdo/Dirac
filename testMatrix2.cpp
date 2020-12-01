#include "Matrix2.h"
#include "Vector2.h"
#include <iostream>


using namespace std;

int main(){

	Matrix2 mat1 = Matrix2(Vector2(rand(), rand()), Vector2(rand(), rand()));
	mat1 *= 2;
	cout << inv(mat1) << endl;
	cout << mat1 * inv(mat1) << endl;






	return 0;
}
