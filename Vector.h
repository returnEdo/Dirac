#include <iostream>
#include <assert.h>
#include <cmath>



class Vector{
	
	public:
	
	double x;
	double y;
	double z;
	
	Vector(double xx, double yy, double zz):
		x(xx),	y(yy),	z(zz)		{}
	
	Vector(const Vector& other):	x(other.x), y(other.y), z(other.z)	{}		
	
	Vector(void):	x(.0),	y(.0),	z(.0)	{}
	
	
	// Let us write a couple of operations
	friend Vector operator +(const Vector& a, const Vector& b);
	friend Vector operator -(const Vector& a, const Vector& b);
	friend double operator *(const Vector& a, const Vector& b);			// scalar product
	
	template <typename T>
	friend Vector operator *(const Vector& a, T c);
	
	template <typename T>
	friend Vector operator /(const Vector& a, T c);
	
	friend Vector operator ^(const Vector& a, const Vector& b);			// vector product
	friend bool operator ==(const Vector& a, const Vector& b);
	
	
	double& operator [](const int indx);								// indexing
	
	Vector& operator +=(const Vector &a);
	Vector& operator -=(const Vector &b);
	
	template <typename T>
	Vector& operator *=(T c);
	
	template <typename T>
	Vector& operator /=(T c);

	friend std::ostream& operator <<(std::ostream& os, const Vector& a);
	
	double norm(void);
	friend double norm(Vector& a);
	
	void normalize(void);
	friend Vector normalize(Vector& a);

	friend double distance(Vector& a, Vector& b);
	double distance(Vector& b);
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
	

template <typename T>
Vector operator *(const Vector& a, T c){
	/* Product by a constant */
	
	return Vector(a.x * double(c), a.y * double(c), a.z * double(c));
} 

template <typename T>
Vector operator /(const Vector& a, T c){
	/* Product by a constant */
	
	assert(double(c) != .0);
	
	return Vector(a.x / double(c), a.y / double(c), a.z / double(c));
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


Vector& Vector::operator +=(const Vector &b){
	
	*this = *this + b;
	
	return *this;
}

Vector& Vector::operator -=(const Vector &b){
	
	*this = *this - b;
	
	return *this;
}

template <typename T>
Vector& Vector::operator *=(T c){
	
	*this = *this * c;
	
	return *this;
}

template <typename T>
Vector& Vector::operator /=(T c){
	
	*this = *this / c;
	
	return *this;
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

//~ double Vector::distance(Vector& b){
	
	//~ return distance(*this, b);
//~ }

