#include "Vector2.h"


Vector2::Vector2(const Vector& other):
	x(other.x),
	y(other.y)		{}



Vector2 operator +(const Vector2& a, const Vector2& b){
	/* Sums between two vectors */
	
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 operator -(const Vector2& a, const Vector2& b){
	/* Difference between two vectors */
	
	return Vector2(a.x - b.x, a.y - b.y);
}


double operator *(const Vector2& a, const Vector2& b){
	/* Scalar product */
	
	return a.x * b.x + a.y * b.y;
}
	

Vector2 operator *(const Vector2& a, double c){
	/* Product by a constant */
	
	return Vector2(a.x * c, a.y * c);
} 

Vector2 operator /(const Vector2& a, double c){
	/* Product by a constant */
	
	assert(c != .0);
	
	return Vector2(a.x / c, a.y / c);
} 


bool operator ==(const Vector2& a, const Vector2& b){
	
	return (a.x == b.x and a.y == b.y);
}



double& Vector2::operator [](const int indx){
	/* works well because x, y and z are protected */
	
	assert(indx >= 0 and indx < 2);
	
	switch (indx){
		
		case 0:			return (this -> x);
		case 1:			return (this -> y);
	}
}


void Vector2::operator +=(const Vector2 &b){
	
	*this = *this + b;
}

void Vector2::operator -=(const Vector2 &b){
	
	*this = *this - b;
}

void Vector2::operator *=(double c){
	
	*this = *this * c;
}

void Vector2::operator /=(double c){
	
	*this = *this / c;
}

std::ostream& operator <<(std::ostream& os, const Vector2& a){
	
	os << '(' << a.x << ',' << a.y << ')';
	
	return os;
}

// norms and normalization
double Vector2::norm(void){
	
	return sqrt((* this) * (* this));
}

double norm(Vector2& a){
	
	return a.norm();
}


double norm2(const Vector2& a){
	return a * a;
}


void Vector2::normalize(void){
	
	*this /= this -> norm();
}

Vector2 normalize(Vector2& a){
	
	Vector2 result;
	
	result = a / a.norm();
	
	return result;
}

// Distance between vectors

double distance(Vector2& a, Vector2& b){
	
	Vector2 c = a - b;
	
	return norm(c);
}


