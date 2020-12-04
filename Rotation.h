#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "Matrix.h"
#include "Vector.h"


class Rotation: public Matrix{
	
	public:

	Vector theta;
	
	Rotation(const Vector& th);
	Rotation(const Rotation& rot)	{ Rotation(rot.theta); }
	Rotation(const Vector& rrow1, const Vector& rrow2, const Vector& rrow3);

	//~ friend Rotation inverse(const Rotation& rot);
	friend double determinant(const Rotation& rot);
	friend bool isSingular(const Rotation& rot)	{ return false; }
	
};

//
//Rotation::Rotation(const Vector& th,  const vector<int>& seq){
//	
//	this -> theta = th;
//	this -> seq = seq;
//	
//	vector<Matrix> matrices = {	Matrix(Vector(1.0, .0, .0),
//									Vector(.0, cos(th.x), -sin(th.x)),
//									Vector(.0, sin(th.x), cos(th.x))),
//								Matrix(Vector(cos(th.y), .0, sin(th.y)),
//									Vector(.0, 1.0, .0),
//									Vector(-sin(th.y), .0, cos(th.y))),
//								Matrix(Vector(cos(th.z), -sin(th.z), .0),
//									Vector(sin(th.z), cos(th.z), .0),
//									Vector(.0, .0, 1.0))};
//				
//	
//	Matrix M;
//	
//	for (auto const& i: seq) { M *= matrices[i - 1]; }
//	
//	this -> row1 = M.row1;
//	this -> row2 = M.row2;
//	this -> row3 = M.row3;
//	
//	this -> buildCol();
//}
//

Rotation::Rotation(const Vector& th){

	this -> row1 = Vector(cos(th.y) * cos(th.z),
			      cos(th.z) * sin(th.x) * sin(th.y) - sin(th.z) * cos(th.x),
			      cos(th.z) * cos(th.x) * sin(th.y) + sin(th.x) * sin(th.z));

	this -> row2 = Vector(cos(th.y) * sin(th.z),
			      sin(th.z) * sin(th.x) * sin(th.y) + cos(th.z) * cos(th.x),
			      sin(th.z) * cos(th.x) * sin(th.y) - sin(th.x) * cos(th.z));

	this -> row3 = Vector(-sin(th.y), cos(th.y) * sin(th.x), cos(th.x) * cos(th.y));

	this -> buildCol();
}


Matrix inverse(const Rotation& rot){
	/* The inverse is simply the transpose */ 
	
	return transpose(rot);
}

double determinant(const Rotation& rot){
	/* It is always one --> orhtogonal transformation */
	
	return 1.0;
}
