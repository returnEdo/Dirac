#include "Matrix2.h"
#include "Vector2.h"
#include <iostream>


using namespace std;

int main(){

	Matrix2 mat1 = Matrix2(Vector2(2, 1), Vector2(2, 3));
	Vector2 vec1 = Vector2(2, 3);
	Vector2 vec2 = Vector2(8, static_cast<double>(1/3));
	cout << (vec2 * vec1) << endl;

	return 0;
}
