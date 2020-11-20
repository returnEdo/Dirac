#pragma once

#include <iostream>
#include <assert.h>
#include "Vector.h"

using namespace std;

class Matrix{
	
	protected:
	
	void buildCol(void);
	
	
	public:
	
	Vector row1;
	Vector row2;
	Vector row3;
	
	Vector col1;
	Vector col2;
	Vector col3;
	
	
	Matrix(const Vector& r1, const Vector& r2, const Vector& r3):
												row1(r1),
												row2(r2),
												row3(r3)		{this -> buildCol();}
	
	Matrix(const Matrix& other):
								row1(other.row1),
								row2(other.row2),
								row3(other.row3)				{this -> buildCol();}
	
	Matrix(void):				row1(Vector(1.0, .0, .0)),
								row2(Vector(.0, 1.0, .0)),
								row3(Vector(.0, .0, 1.0))		{this -> buildCol();}
								
								

	friend Matrix operator *(const Matrix& a, double b);
	friend Matrix operator *(const Matrix& a, const Matrix& b);
	friend Vector operator *(const Matrix& a, const Vector& b);
	void operator *=(double b);
	void operator *=(const Matrix& b);
	
	friend Matrix operator /(const Matrix& a, double b);
	void operator /=(double b);
	
	friend Matrix operator +(const Matrix& a, const Matrix& b);
	void operator +=(const Matrix& b);
	
	friend Matrix operator -(const Matrix& a, const Matrix& b);
	void operator -=(const Matrix& b);
	
	
	friend double det(const Matrix& a);
	friend bool isSingular(const Matrix& a)	{ return (det(a) == .0); }
	
	friend Matrix transpose(const Matrix& a);
	friend Matrix inv(const Matrix& a);

	friend std::ostream& operator <<(std::ostream& os, const Matrix& a);
	
};



void Matrix::buildCol(void){
	/* Builds the column */
	
	this -> col1 = Vector(row1.x, row2.x , row3.x);
	this -> col2 = Vector(row1.y, row2.y , row3.y);
	this -> col3 = Vector(row1.z, row2.z , row3.z);
}


Matrix operator *(const Matrix& a, double b){
	
	return Matrix(a.row1 * b, a.row2 * b, a.row3 * b);
}


Matrix operator *(const Matrix& a, const Matrix& b){

	Vector res1 = Vector(a.row1 * b.col1, a.row1 * b.col2, a.row1 * b.col3);
	Vector res2 = Vector(a.row2 * b.col1, a.row2 * b.col2, a.row2 * b.col3);
	Vector res3 = Vector(a.row3 * b.col1, a.row3 * b.col2, a.row3 * b.col3);

	return Matrix(res1, res2, res3);
}


Vector operator *(const Matrix& a, const Vector& b){
	
	return Vector(a.row1 * b, a.row2 * b, a.row3 * b);
}


void Matrix::operator *=(double b){
	
	*this = *this * b;
}


void Matrix::operator *=(const Matrix& b){
	
	*this = *this * b;
}


Matrix operator /(const Matrix& a, double b){
	
	assert(b != .0);
	
	return Matrix(a.row1 / b, a.row2 / b, a.row3 / b);
}


void Matrix::operator /=(double b){
	
	*this = *this / b;
}


Matrix operator +(const Matrix& a, const Matrix& b){
	
	return Matrix(a.row1 + b.row1, a.row2 + b.row2, a.row3 + b.row3);
}

void Matrix::operator +=(const Matrix& b){
	
	*this = *this + b;
}

Matrix operator -(const Matrix& a, const Matrix& b){
	
	return Matrix(a.row1 - b.row1, a.row2 - b.row2, a.row3 - b.row3);
}

void Matrix::operator -=(const Matrix& b){
	
	*this = *this - b;
}



double det(const Matrix& a){
	
	return a.row1.x * a.row2.y * a.row3.z + 
		   a.row1.y * a.row2.z * a.row3.x + 
		   a.row1.z * a.row2.x * a.row3.y - 
		   a.row1.z * a.row2.y * a.row3.x - 
		   a.row1.x * a.row2.z * a.row3.y - 
		   a.row1.y * a.row2.x * a.row3.z;
} 


Matrix transpose(const Matrix& a){
	
	return Matrix(a.col1, a.col2, a.col3);
}


Matrix inv(const Matrix& a){
	
	double dt = det(a);
	
	assert(dt != .0);
	
	Vector r1 = Vector(a.row2.y * a.row3.z - a.row2.z * a.row3.y,
					   a.row2.z * a.row3.x - a.row2.x * a.row3.z,
					   a.row2.x * a.row3.y - a.row2.y * a.row3.x);
	
	Vector r2 = Vector(a.row3.y * a.row1.z - a.row3.z * a.row1.y,
					   a.row3.z * a.row1.x - a.row3.x * a.row1.z,
					   a.row3.x * a.row1.y - a.row3.y * a.row1.x);
	
	Vector r3 = Vector(a.row1.y * a.row2.z - a.row1.z * a.row2.y,
    				   a.row1.z * a.row2.x - a.row1.x * a.row2.z,
    				   a.row1.x * a.row2.y - a.row1.y * a.row2.x);
    
    return transpose(Matrix(r1, r2, r3)) / dt;
}
    
std::ostream& operator <<(std::ostream& os, const Matrix& a){
	
	os << a.row1.x << ' ' << a.row1.y << ' ' << a.row1.z << '\n' <<
		  a.row2.x << ' ' << a.row2.y << ' ' << a.row2.z << '\n' <<
		  a.row3.x << ' ' << a.row3.y << ' ' << a.row3.z << '\n';
	
	return os;
}
		



