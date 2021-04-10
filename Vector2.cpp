#include "Vector2.h"

#include <assert.h>
#include <cmath>

Vector2::Vector2(float xx, float yy):  			x(xx),	y(yy)		{}
Vector2::Vector2(const Vector2& other):			x(other.x), y(other.y)	{}		
Vector2::Vector2(const std::vector<float>& other): 	x(other[0]), y(other[1])	{}
Vector2::Vector2(float xyz):				x(xyz), y(xyz)	{}
Vector2::Vector2(void):					x(.0),	y(.0)	{}

void Vector2::getRaw(float* data) const{

	data[0] = x;
	data[1] = y;
}

Vector2 operator +(const Vector2& a, const Vector2& b){
	
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator -(const Vector2& a, const Vector2& b){
	
	return Vector2(a.x - b.x, a.y - b.y);
}


float operator *(const Vector2& a, const Vector2& b){
	
	return a.x * b.x + a.y * b.y;
}
	

Vector2 operator *(const Vector2& a, float c){
	
	return Vector2(a.x * c, a.y * c);
} 

Vector2 operator /(const Vector2& a, float c){
	
	//assert(c != .0);
	
	return Vector2(a.x / c, a.y / c);
} 


float operator ^(const Vector2& a, const Vector2& b){
	
	Vector2 result;
	
	return (a.x * b.y - a.y * b.x);
}


bool operator ==(const Vector2& a, const Vector2& b){
	
	return (a.x == b.x and a.y == b.y);
}

Vector2 operator %(const Vector2& a, const Vector2& b){

	return Vector2(a.x * b.x, a.y * b.y);
}



float& Vector2::operator [](const int indx){
	
	assert(indx == 0 or indx == 1);
	
	switch (indx){
		
		case 0:			return (this -> x);
		case 1:			return (this -> y);
	}
	return x;
}

void Vector2::operator =(const Vector2& a){

	x = a.x;
	y = a.y;
}


void Vector2::operator +=(const Vector2& b){
	
	*this = *this + b;
}

void Vector2::operator -=(const Vector2& b){
	
	*this = *this - b;
}

void Vector2::operator *=(float c){
	
	*this = *this * c;
}

void Vector2::operator /=(float c){
	
	*this = *this / c;
}

std::ostream& operator <<(std::ostream& os, const Vector2& a){
	
	os << '(' << a.x << ',' << a.y << ')';
	
	return os;
}

float Vector2::norm(void) const{
	
	return sqrt((* this) * (* this));
}

float norm2(const Vector2& a){

	return (a * a);
}


float norm(Vector2& a){
	
	return a.norm();
}

Vector2 abs(const Vector2& a){
	
	return Vector2(a.x >= .0f? a.x: -a.x,
		      a.y >= .0f? a.y: -a.y);
}

void Vector2::normalize(void){
	
	*this /= this -> norm();
}

Vector2 normalize(Vector2& a){
	
	Vector2 result;
	
	result = a / a.norm();
	
	return result;
}


float distance(const Vector2& a, const Vector2& b){
	
	Vector2 c = a - b;
	
	return norm(c);
}

bool nonNegative(const Vector2& a){

	return (a.x >= 0.0 and  a.y >= 0.0);
}


