#include <iostream>
#include <assert.h>

using namespace std;

class Vector;

class Matrix{
	
	private:
	
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
								
								

	friend Matrix operator *(const Matrix& a, const Matrix& b);			// matrix multiplication
	Matrix operator *(const Matrix& other);
	
	friend Vector operator *(const Matrix& a, const Vector& b);			// mat vec multiplication
	Vector operator *(const Vector& other);
	
	friend Matrix operator *(const Matrix& a, double c);
	Matrix operator *(double c);
	Matrix operator /(double c);
	
	friend Matrix operator +(const Matrix& a, const Matrix& b);			// mat sum and diff
	Matrix operator +(const Matrix& b);
	
	friend Matrix operator -(const Matrix& a, const Matrix& b);
	Matrix operator -(const Matrix& b);
	
	void operator +=(const Matrix& b);									// update this
	void operator -=(const Matrix& b);
	void operator *=(const Matrix& b);
	void operator *=(double c);
	void operator /=(double c);
	
	friend Matrix transpose(const Matrix& b);
	void transpose(void);
	
	friend double det(const Matrix& b);
	double det(void);
	
	bool isInvertible(void)		{ return (this -> det() != .0); }
	

	friend std::ostream& operator <<(std::ostream& os, const Matrix& a);
	
};



void Matrix::buildCol(void){
	/* Builds the column */
	
	this -> col1 = Vector(row1.x, row2.x , row3.x);
	this -> col2 = Vector(row1.y, row2.y , row3.y);
	this -> col3 = Vector(row1.z, row2.z , row3.z);
}

Matrix operator *(const Matrix& a, const Matrix& b){
	/* Matrix matrix multiplication */

	Vector resRow1 = Vector(a.row1 * b.col1, a.row1 * b.col2, a.row1 * b.col3);
	Vector resRow2 = Vector(a.row2 * b.col1, a.row2 * b.col2, a.row2 * b.col3);
	Vector resRow3 = Vector(a.row3 * b.col1, a.row3 * b.col2, a.row3 * b.col3);
	
	return Matrix(resRow1, resRow2, resRow3);	
}

Matrix Matrix::operator *(const Matrix& b){
	/* Matrix matrix multiplication */
	
	return (*this) * b;
}


Vector operator *(const Matrix& a, const Vector& b){
	/* mat vec mult */
	
	return Vector(a.row1 * b, a.row2 * b, a.row3 * b);
}	


Vector Matrix::operator *(const Vector& b){
	/* matrix vector multiplication */
	
	return (*this) * b;
}

Matrix operator *(Matrix& a, double c){
	
	return Matrix(a.row1 * c, a.row2 * c, a.row3 * c);
}


Matrix Matrix::operator *(double c){
	
	std::cout << 1000 << std::endl;
	
	Matrix res = (*this) * c;
	
	
	return res;
}

Matrix operator /(const Matrix& a, double c){
	/* Division by a scalar */
	
	assert(c != 0.0);
	
	return a * (1 / c);
}

Matrix Matrix::operator /(double c){
	
	return (*this) / c;
}

Matrix operator +(const Matrix& a, const Matrix& b){
	/* Matrix addition */
	
	return Matrix(a.row1 + b.row1, a.row2 + b.row2, a.row3 + b.row3);
}


Matrix Matrix::operator +(const Matrix& b){
	
	return (*this) + b;
}

Matrix operator -(const Matrix& a, const Matrix& b){
	/* Matrix addition */
	
	return Matrix(a.row1 - b.row1, a.row2 - b.row2, a.row3 - b.row3);
}


Matrix Matrix::operator -(const Matrix& b){
	
	return (*this) - b;
}


void Matrix::operator +=(const Matrix& b){
	
	(*this) = (*this) + b;
}

void Matrix::operator -=(const Matrix& b){

	(*this) = (*this) - b;
}

void Matrix::operator *=(const Matrix& b){

	(*this) = (*this) * b;
}

void Matrix::operator *=(double b){
	
	(*this) = (*this) * b;
}

void Matrix::operator /=(double b){
	
	(*this) = (*this) / b;
}


//~ Matrix transpose(const Matrix& a){
	
	//~ return Matrix(a.col1, a.col2, a.col2);
//~ }

//~ void Matrix::transpose(void){
	//~ /* Transposition */

	//~ *this = transpose(*this);
//~ }

//~ double det(const Matrix& b){
	//~ /* Calculates the determinant of b */
	
	//~ return b.row1.x * b.row2.y * b.row3.z + 
		   //~ b.row1.y * b.row2.z * b.row3.x +
		   //~ b.row1.z * b.row2.x * b.row3.y -
		   //~ b.row1.z * b.row2.y * b.row3.x -
	       //~ b.row1.y * b.row2.x * b.row3.z -
	       //~ b.row1.x * b.row2.z * b.row3.y;
//~ }
	

//~ double Matrix::det(void){
	
	//~ return det(*this);
//~ }	


std::ostream& operator <<(std::ostream& os, const Matrix& a){
	
	os << a.row1.x << ' ' << a.row1.y << ' ' << a.row1.z << '\n' <<
		  a.row2.x << ' ' << a.row2.y << ' ' << a.row2.z << '\n' <<
		  a.row3.x << ' ' << a.row3.y << ' ' << a.row3.z << '\n';
	
	return os;
}
		



