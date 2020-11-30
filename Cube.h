#include <iostream>
#include <vector>
#include "Vector.h"
#include "Object.h"


vector<vector<int> > BUFFER = {{0, 1, 2}, {0, 2, 3}, {1, 5, 6}, {1, 6, 2},
			       {5, 4, 7}, {5, 7, 6}, {4, 0, 3}, {4, 3, 7},
			       {3, 2, 6}, {3, 6, 7}, {4, 0, 1}, {4, 1, 5}};

vector<Vector> Model = {Vector(-1, -1, -1),
			Vector(-1, 1, -1),
			Vector(1, 1, -1),
			Vector(1, -1, -1),
			Vector(-1, -1, 1),
			Vector(-1, 1, 1),
			Vector(1, 1, 1),
			Vector(1, -1, 1)};


class Cube: public Object{
	
	protected:
	
	vector<vector<Vector> >  x;

	vector<vector<double> > color;
	
	Vector xcg;				
	Vector theta;			
	
	double z0;
	
	vector<vector<int> > indexBuffer;	
	
	
	public:
	
	Cube(const Vector& xcg0 = Vector(),
	     const Vector& theta0 = Vector());
	           
};



Cube::Cube(const Vector& xgc0, const Vector& theta0):
		Object::Object(BUFFER, Model, xgc0, theta0)
{}
	
