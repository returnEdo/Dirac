#include <iostream>
#include <vector>
#include "Vector.h"
#include "Object.h"


vector<vector<int> > BUFFER = {{0, 1, 2}};

vector<Vector> Model = {Vector(.0, 1, .0), Vector(1, .0, .0), Vector(.0, -1.0, .0)};



class Triangle: public Object{
	
	protected:
	
	vector<vector<Vector> > x;
	
	vector<vector<double> > color;

	vector<vector<int> > indexBuffer;	
	Vector xcg;				
	Vector theta;			
	
	double z0;
	int n;
	
	
	public:
	
	Triangle(const Vector& xcg0 = Vector(),
	     const Vector& theta0 = Vector());
	           
};



Triangle::Triangle(const Vector& xgc0, const Vector& theta0):
	      Object::Object(BUFFER, Model, xgc0, theta0)
{}
	
