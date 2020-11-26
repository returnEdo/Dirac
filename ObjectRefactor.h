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

	Vector xcg;															// center of mass position
	Vector theta;														// Euler angles
	
	vector<vector<Vector> > x;			// the order is Model, Camera, Pixel

	double z0;
	int n;
		
	vector<vector<int> > indexBuffer;											// index buffer (group of three)
	
	vector<Vector> normals;

	public:
	
	Object(const vector<vector<int> >& iB,
		   const vector<Vector>& xM0,
		   const Vector& xcg0 = Vector(),
		   const Vector& theta0 = Vector(),
		   double z00 = 1.0):
			indexBuffer(iB);
		   
	Object(const Object& obj):
		indexBuffer(obj.indexBuffer),
		x(obj.x),
		theta(obj.theta),
		xcg(obj.xcg),
		z0(obj.z0),
		n(obj.n)	{}
						
	void updateVertices(const Camera& cam);

	const vector<vector<int> >& getIndexBuffer(void) const;
	void updateAttitude(double delta)	{ theta.x += delta; }			// this shit is only for debugging
	
	friend void rasterizeObject(const Object&);
	friend Rasterizer;
};


Object::Object(const vector<vector<int> >& iB,
	       const vector<Vector>& xM0,
	       const Vector& xg0 = Vector(),
	       const Vector& theta0 = Vector(),
	       double z0 = 1.0):
	xcg(xg0),
	theta(theta0),
	z0(z00),
	indexBuffer(iB) {

	for (auto const& xMi: xM0){

		(this -> x).push_back({xM0, xM0, xM0});
	}

	n = (this -> indexBuffer).size();
}




void Object::updateVertices(const Camera& cam){
	/* Finds the cam vertices and the Pixel vertices */

	Rotation Mtheta = Rotation(this -> theta, {1, 2, 3});
	Rotation MthetaCam = Rotation(cam.thetaCam, {3, 2, 1});
	double tphi = tan(cam.phi);

	for (int i = 0; i < (this -> n); i++){
		/* Update of the cam vertices  */
		x[i][1] = (MthetaCam * ((Mtheta * x[i][0]) * z0 +
				this -> xcg - cam.xCam));
	
		/* Update of the pixel vertices  */
		x[i][2] = Vector(cam.W / 2.0 * x[i][1].y / (x[i][1].z * tphi),
				 cam.W / 2.0 * x[i][1].x / (x[i][1].z * tphi),
				 x[i][1].z);
	
	
	}

}
