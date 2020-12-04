#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Vector.h"
#include "Rotation.h"
#include "Camera.h"
#include "OBJParser.h"

class Rasterizer;


#ifndef BUFFERS_STRUCT
#define BUFFERS_STRUCT
struct Buffers{

	vector<vector<int> > indexBuffer;
	vector<vector<int> > uvBuffer;
	vector<vector<int> > normalBuffer;
};
#endif


class Object{


	private:

	Rotation Mtheta;

	
	public:
	
	vector<vector<Vector> > x;	// M, W, C, P 
	vector<Vector> normals;
	vector<Vector2> uvs;

	Buffers buffers;

	Vector xcg;
	Vector theta;
	

	int n;
	double z0;

	Object(const string& address,
	       const Vector& xg0 = Vector(),
	       const Vector& theta0 = Vector(),
	       double z00 = 1.0);
	
	void updateVertices(const Camera& cam);
	
	const vector<vector<int> >& getIndexBuffer(void) const;
	void updateAttitude(double delta)	{ theta.x += delta; }

	friend void rasterizeObject(const Object&);
	friend Rasterizer;
};


Object::Object(const string& address,
	       const Vector& xg0,
	       const Vector& theta0,
	       double z00):
			xcg(xg0), theta(theta0), z0(z00), Mtheta(Rotation(theta0)) {
	
	vector<Vector> xM;
	
	getObject(address, xM, this -> normals, this -> uvs, this -> buffers);

	for (auto const& xi: xM){

		(this -> x).push_back({xi, xi, xi, xi});
	}

	this -> n = x.size();	
}




void Object::updateVertices(const Camera& cam){
	/* Finds the cam vertices */
	
	Mtheta = Rotation(this -> theta);
	Rotation MthetaCam = Rotation(cam.thetaCam);
	double tphi = tan(cam.phi);

	for (int i = 0; i < this -> n; i++){
		
		/* world coordinates  */
		x[i][1] = (Mtheta * x[i][0]) * z0 + this -> xcg;
		
		/* camera coordinates  */
		x[i][2] = MthetaCam * (x[i][1] - cam.xCam);


		/* Pixel coordinates  */
		x[i][3] = Vector(cam.W / 2.0 * x[i][2].y / (x[i][2].z * tphi),
				 cam.W / 2.0 * x[i][2].x / (x[i][2].z * tphi),
				 1 / x[i][2].z);					// returns the inverse
	}
}

const vector<vector<int> >& Object::getIndexBuffer(void) const{  return (this -> buffers.indexBuffer); }

