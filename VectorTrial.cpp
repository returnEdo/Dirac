#include <iostream>
#include "Vector.h"

using namespace std;

int main(void){
	
	Vector vec1 = Vector(1, 1, 1);
	Vector vec2 = Vector(0, 4, 3);
	Vector vec3 = Vector(1, 0, 0);
	Vector vec4 = Vector(0, 1, 0);
	
	
	cout << vec1 << endl;
	cout << vec2 << endl;
	
	cout << vec1 * vec2 << endl;
	cout << (vec3^vec4) << endl;
	
	cout << norm(vec2) << endl;
	cout << vec2.norm() << endl;
	
	Vector vec5 = vec2 + vec3;
	vec2 += vec3;
	
	cout << vec5 << endl;
	cout << vec2 << endl;
	
	vec3.normalize();
	cout << vec3 << endl;
	
	double d = distance(vec3, vec4);
	cout << d << endl;
	
	cout << vec4 << endl;
	
	vec4 /= 10;
	cout << vec4 << endl;
	
	cout << vec4[1] << endl;
	cout << vec4.y << endl;
	
	return 0;
}
