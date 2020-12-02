#pragma once

#include <iostream>
#include <assert.h>
#include <cmath>
#include <vector>

class Vector{
	
	public:
	
	double x;
	double y;
	double z;
	
	Vector(double xx, double yy, double zz):
		x(xx),	y(yy),	z(zz)		{}
	
	Vector(const Vector& other):	x(other.x), y(other.y), z(other.z)	{}		
	Vector(const std::vector<double>& other): x(other[0]), y(other[1]), z(other[2])	{}

	Vector(void):	x(.0),	y(.0),	z(.0)	{}
	
	// Let us write a couple of operations
	friend Vector operator +(const Vector& a, const Vector& b);
	friend Vector operator -(const Vector& a, const Vector& b);
	friend double operator *(const Vector& a, const Vector& b);			// scalar product
	
	friend Vector operator *(const Vector& a, double c);
	
	friend Vector operator /(const Vector& a, double c);
	
	friend Vector operator ^(const Vector& a, const Vector& b);			// vector product
	friend bool operator ==(const Vector& a, const Vector& b);	
	
	double& operator [](const int indx);								// indexing
	
	void operator +=(const Vector &a);
	void operator -=(const Vector &b);

	void operator *=(double c);

	void operator /=(double c);

	friend std::ostream& operator <<(std::ostream& os, const Vector& a);
	
	double norm(void);
	friend double norm(Vector& a);
	
	void normalize(void);
	friend Vector normalize(Vector& a);

	friend double distance(Vector& a, Vector& b);

	friend bool nonNegative(const Vector& a);
};


Vector operator +(const Vector& a, const Vector& b){
	/* Sums between two vectors */
	
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator -(const Vector& a, const Vector& b){
	/* Difference between two vectors */
	
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}


double operator *(const Vector& a, const Vector& b){
	/* Scalar product */
	
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
	

Vector operator *(const Vector& a, double c){
	/* Product by a constant */
	
	return Vector(a.x * c, a.y * c, a.z * c);
} 

Vector operator /(const Vector& a, double c){
	/* Product by a constant */
	
	assert(c != .0);
	
	return Vector(a.x / c, a.y / c, a.z / c);
} 


Vector operator ^(const Vector& a, const Vector& b){
	/* Vector product */
	
	Vector result;
	
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	
	return result;
}


bool operator ==(const Vector& a, const Vector& b){
	
	return (a.x == b.x and a.y == b.y and a.z == b.z);
}



double& Vector::operator [](const int indx){
	/* works well because x, y and z are protected */
	
	assert(indx >= 0 and indx <= 2);
	
	switch (indx){
		
		case 0:			return (this -> x);
		case 1:			return (this -> y);
		case 2:			return (this -> z);
	}
}


void Vector::operator +=(const Vector &b){
	
	*this = *this + b;
}

void Vector::operator -=(const Vector &b){
	
	*this = *this - b;
}

void Vector::operator *=(double c){
	
	*this = *this * c;
}

void Vector::operator /=(double c){
	
	*this = *this / c;
}

std::ostream& operator <<(std::ostream& os, const Vector& a){
	
	os << '(' << a.x << ',' << a.y << ',' << a.z << ')';
	
	return os;
}

// norms and normalization
double Vector::norm(void){
	
	return sqrt((* this) * (* this));
}

double norm(Vector& a){
	
	return a.norm();
}

void Vector::normalize(void){
	
	*this /= this -> norm();
}

Vector normalize(Vector& a){
	
	Vector result;
	
	result = a / a.norm();
	
	return result;
}

// Distance between vectors

double distance(Vector& a, Vector& b){
	
	Vector c = a - b;
	
	return norm(c);
}

bool nonNegative(const Vector& a){

	return (a.x >= 0.0 and  a.y >= 0.0 and a.z >= 0.0);
}


