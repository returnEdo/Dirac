#include <iostream>
#include <vector>
#include "Vector.h"
#include "Object.h"


vector<vector<int> > BUFFER = {{1, 5, 4}, {1, 0, 4}, {2, 0, 1},
							   {2, 3, 0}, {6, 3, 2}, {6, 7, 2},
							   {5, 7, 6}, {5, 4, 7}, {6, 1, 5},
							   {6, 2, 1}, {3, 4, 0}, {3, 7, 4}};
							   
vector<Vector> Model = {Vector(1, 1, -1), Vector(1, -1, -1),
						Vector(-1, -1, -1), Vector(-1, 1, -1),
						Vector(1, 1, 1), Vector(1, -1, 1),
						Vector(-1, -1, 1), Vector(-1, 1, 1)};



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
	
