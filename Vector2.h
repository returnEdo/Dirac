#pragma once

#include <iostream>
#include <assert.h>
#include <cmath>
#include "Vector.h"

using namespace std;


class Vector2{
	
	public:
	
	double x;
	double y;
	
	Vector2(double xx, double yy):
		x(xx),	y(yy)		{}
	
	Vector2(const Vector2& other):	x(other.x), y(other.y)	{}		
	Vector2(const Vector& other);

	Vector2(void):	x(.0),	y(.0)	{}
	
	// Let us write a couple of operations
	friend Vector2 operator +(const Vector2& a, const Vector2& b);
	friend Vector2 operator -(const Vector2& a, const Vector2& b);
	friend double operator *(const Vector2& a, const Vector2& b);			// scalar product
	
	friend Vector2 operator *(const Vector2& a, double c);
	
	friend Vector2 operator /(const Vector2& a, double c);
	
	friend bool operator ==(const Vector2& a, const Vector2& b);
	
	
	double& operator [](const int indx);								// indexing
	
	void operator +=(const Vector2 &a);
	void operator -=(const Vector2 &b);

	void operator *=(double c);

	void operator /=(double c);

	friend std::ostream& operator <<(std::ostream& os, const Vector2& a);
	
	double norm(void);
	friend double norm2(const Vector2& a);
	friend double norm(Vector2& a);
	
	void normalize(void);
	friend Vector2 normalize(Vector2& a);

	friend double distance(Vector2& a, Vector2& b);
};


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


