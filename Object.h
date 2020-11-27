#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.h"
#include "Rotation.h"
#include "Camera.h"

class Rasterizer;


class Object{
	
	protected:
	
	vector<vector<Vector> > x;	// M, W, C, P												// model vertices
	vector<vector<double> > color;		// color of the face
	vector<vector<int> > indexBuffer;											// index buffer (group of three)
	
	Vector xcg;
	Vector theta;


	int n;
	double z0;
	
	
	public:
	
	Object(const vector<vector<int> >& iB,
		   const vector<Vector>& xM0,
		   const Vector& xcg0 = Vector(),
		   const Vector& theta0 = Vector(),
		   const vector<vector<double> >& clr = {{}},
		   double z00 = 1.0);
		   
	Object(const Object& obj):
		indexBuffer(obj.indexBuffer),
		x(obj.x),
		xcg(obj.xcg),
		theta(obj.theta),
		z0(obj.z0),
		color(obj.color),
		n(obj.n)	{}
		
	void updateVertices(const Camera& cam);
	
	const vector<vector<int> >& getIndexBuffer(void) const;
	void updateAttitude(double delta)	{ theta.x += delta; }			// this shit is only for debugging

	Vector findVectorGivenX(Vector&, Vector&, double);
	Vector findVectorGivenY(Vector&,  Vector&, double);


	friend void rasterizeObject(const Object&);
	friend Rasterizer;
};

Object::Object(const vector<vector<int> >& iB,
		   const vector<Vector>& xM0,
		   const Vector& xcg0,
		   const Vector& theta0,
		   const vector<vector<double> >& clr,
		   double z00):
			indexBuffer(iB),
	    		xcg(xcg0),
	    		theta(theta0),
	    		z0(z00),
			color(clr){

	for (auto const& xi: xM0){

		(this -> x).push_back({xi, xi, xi, xi});
	}
	this -> n = xM0.size();
}	
	

void Object::updateVertices(const Camera& cam){
	/* Finds the cam vertices */
	
	Rotation Mtheta = Rotation(this -> theta, {1, 2, 3});
	Rotation MthetaCam = Rotation(cam.thetaCam, {3, 2, 1});
	double tphi = tan(cam.phi);

	for (int i = 0; i < this -> n; i++){
		
		/* world coordinates  */
		x[i][1] = (Mtheta * x[i][0]) * z0 + this -> xcg;
		
		/* camera coordinates  */
		x[i][2] = MthetaCam * (x[i][1] - cam.xCam);


		/* Pixel coordinates  */
		x[i][3] = Vector(cam.W / 2.0 * x[i][2].y / (x[i][2].z * tphi),
				 cam.W / 2.0 * x[i][2].x / (x[i][2].z * tphi),
				 x[i][2].z);

	}
}

const vector<vector<int> >& Object::getIndexBuffer(void) const{  return (this -> indexBuffer); }


Vector Object::findVectorGivenX(Vector& vec1, Vector& vec2, double x){
	/* this method is used in the rasterizer  */
	
	double alpha = (x - vec2.x) / (vec1.x - vec2.x);
	
	return Vector(x,
		      vec1.y * alpha + (1 - alpha) * vec2.y,
		      vec1.z * alpha + (1 - alpha) * vec2.z);
}


Vector Object::findVectorGivenY(Vector& vec1, Vector& vec2, double y){

	double alpha = (y - vec2.y) / (vec1.y - vec2.y);

	return Vector(vec1.x * alpha + (1 - alpha) * vec2.x,
		      y,
		      vec1.z * alpha + (1 - alpha) * vec2.z);
}





