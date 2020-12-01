#pragma once

#include <iostream>
#include <assert.h>
#include "Vector2.h"

using namespace std;

class Matrix2{
	
	protected:
	
	void buildCol(void);
	
	
	public:
	
	Vector2 row1;
	Vector2 row2;
	
	Vector2 col1;
	Vector2 col2;
	
	
	Matrix2(const Vector2& r1, const Vector2& r2):
							row1(r1),
							row2(r2)	{this -> buildCol();}
	
	Matrix2(const Matrix2& other):
							row1(other.row1),
							row2(other.row2)	{this -> buildCol();}
	
	Matrix2(void):				row1(Vector2(1.0, .0)),
						row2(Vector2(.0, 1.0))		{this -> buildCol();}
								
								

	friend Matrix2 operator *(const Matrix2& a, double b);
	friend Matrix2 operator *(const Matrix2& a, const Matrix2& b);
	friend Vector2 operator *(const Matrix2& a, const Vector2& b);
	void operator *=(double b);
	void operator *=(const Matrix2& b);
	
	friend Matrix2 operator /(const Matrix2& a, double b);
	void operator /=(double b);
	
	friend Matrix2 operator +(const Matrix2& a, const Matrix2& b);
	void operator +=(const Matrix2& b);
	
	friend Matrix2 operator -(const Matrix2& a, const Matrix2& b);
	void operator -=(const Matrix2& b);
	
	
	friend double det(const Matrix2& a);
	friend bool isSingular(const Matrix2& a)	{ return (det(a) == .0); }
	
	friend Matrix2 transpose(const Matrix2& a);
	friend Matrix2 inv(const Matrix2& a);

	friend std::ostream& operator <<(std::ostream& os, const Matrix2& a);
	
};



void Matrix2::buildCol(void){
	/* Builds the column */
	
	this -> col1 = Vector2(row1.x, row2.x);
	this -> col2 = Vector2(row1.y, row2.y);
}


Matrix2 operator *(const Matrix2& a, double b){
	
	return Matrix2(a.row1 * b, a.row2 * b);
}


Matrix2 operator *(const Matrix2& a, const Matrix2& b){

	Vector2 res1 = Vector2(a.row1 * b.col1, a.row1 * b.col2);
	Vector2 res2 = Vector2(a.row2 * b.col1, a.row2 * b.col2);
	
	cout << a.row2 * b.col1 << endl;
	return Matrix2(res1, res2);
}


Vector2 operator *(const Matrix2& a, const Vector2& b){
	
	return Vector2(a.row1 * b, a.row2 * b);
}


void Matrix2::operator *=(double b){

	*this = *this * b;
}


void Matrix2::operator *=(const Matrix2& b){
	
	*this = *this * b;
}


Matrix2 operator /(const Matrix2& a, double b){
	
	assert(b != .0);
	
	return Matrix2(a.row1 / b, a.row2 / b);
}


void Matrix2::operator /=(double b){
	
	*this = *this / b;
}


Matrix2 operator +(const Matrix2& a, const Matrix2& b){
	
	return Matrix2(a.row1 + b.row1, a.row2 + b.row2);
}

void Matrix2::operator +=(const Matrix2& b){
	
	*this = *this + b;
}

Matrix2 operator -(const Matrix2& a, const Matrix2& b){
	
	return Matrix2(a.row1 - b.row1, a.row2 - b.row2);
}

void Matrix2::operator -=(const Matrix2& b){
	
	*this = *this - b;
}



double det(const Matrix2& a){

	return a.row1.x * a.row2.y - a.row1.y * a.row2.x;	
} 


Matrix2 transpose(const Matrix2& a){
	
	return Matrix2(a.col1, a.col2);
}


Matrix2 inv(const Matrix2& a){
	
	double dt = det(a);
	cout << dt << endl;	
	assert(dt != .0);
	
	Vector2 r1 = Vector2(a.row2.y, - a.row1.y);
	Vector2 r2 = Vector2(-a.row2.x, a.row1.x);

    return Matrix2(r1, r2) / dt;
}
    
std::ostream& operator <<(std::ostream& os, const Matrix2& a){
	
	os << a.row1.x << ' ' << a.row1.y << "\n" <<
		  a.row2.x << ' ' << a.row2.y;
	
	return os;
}
		



