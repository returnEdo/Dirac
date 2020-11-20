#include <iostream>
#include "Rotation.h"
#include "Vector.h"
#include <cmath>

using namespace std;

int main(){
	
	
	
	Rotation rot1 = Rotation(Vector(M_PI / 3, .0, .0));

	Vector y = Vector(.0, 1.0, .0);
	
	cout << rot1 << endl;
	cout << inverse(rot1) << endl;
	
	Matrix mat1 = inverse(rot1);
	
	cout << (rot1 * mat1) << endl;
	cout << (rot1.row2 * inverse(rot1).col2) << endl;
	cout << (rot1.row2) << endl;
	cout << (inverse(rot1).col2) << endl;
	
	return 0;
}
