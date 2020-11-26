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
	
	vector<Vector> xM;													// model vertices
	vector<Vector> xN;													// normalized vertices
	vector<Vector> xP;													// pixel frame (refactored are centered)
	vector<Vector> xC;													// cam basis
	
	Vector xcg;															// center of mass position
	Vector theta;														// Euler angles
	
	double z0;
	
	vector<vector<int> > indexBuffer;											// index buffer (group of three)
	
	public:
	
	Object(const vector<vector<int> >& iB,
		   const vector<Vector>& xM0,
		   const Vector& xcg0 = Vector(),
		   const Vector& theta0 = Vector(),
		   double z00 = 1.0):
			indexBuffer(iB),
	    	xM(xM0),
	    	xN(xM0),
	    	xP(xM0),
	    	xC(xM0),
	    	xcg(xcg0),
	    	theta(theta0),
	    	z0(z00)					{}		   
		   
	Object(const Object& obj):
		indexBuffer(obj.indexBuffer),
		xM(obj.xM),
		xN(obj.xN),
		xP(obj.xP),
		xC(obj.xC),
		xcg(obj.xcg),
		theta(obj.theta),
		z0(obj.z0)					{}
		
	void updateCamVertices(const Camera& cam);
	void updatePixelVertices(const Camera& cam);
	void updateNormalizedVertices(const Camera& cam);
	
	const vector<Vector>& getNormalizedVertices(void) const;
	const vector<vector<int> >& getIndexBuffer(void) const;
	void updateAttitude(double delta)	{ theta.x += delta; }			// this shit is only for debugging
	
	friend void rasterizeObject(const Object&);
	friend Rasterizer;
};


void Object::updateCamVertices(const Camera& cam){
	/* Finds the cam vertices */

	(this -> xC).clear();												// get rid of the previous iteration

	Rotation Mtheta = Rotation(this -> theta, {1, 2, 3});
	Rotation MthetaCam = Rotation(cam.thetaCam, {3, 2, 1});
	
	for (auto const& mVertex: this -> xM){
		
		(this -> xC).push_back(MthetaCam * ((Mtheta * mVertex) * z0 +
				this -> xcg - cam.xCam));
	}
}



void Object::updatePixelVertices(const Camera& cam){
	/* Finds the vertices in the pixel frame ready to be displayed */

	// should update cam vertices before and update width and height of cam
	
	(this -> xP).clear();
	
	double tphi = tan(cam.phi);
	
	for (auto const& cVertex: this -> xC){
		
		(this -> xP).push_back(Vector(cam.W / 2.0 * cVertex.y / (cVertex.z * tphi),
					      cam.W / 2.0 *cVertex.x / (cVertex.z * tphi),
					      cVertex.z));
	}
}


void Object::updateNormalizedVertices(const Camera& cam){
	/* Finds the vertices in the normalized frame ready to be displayed */

	// should update cam vertices before and update width and height of cam
	
	(this -> xN).clear();
	
	double tphi = tan(cam.phi);
	
	for (auto const& cVertex: this -> xC){
		
		(this -> xN).push_back(Vector(cVertex.y / (cVertex.z * tphi),
									  cam.W / cam.H * cVertex.x / (cVertex.z * tphi),
									  cVertex.z));
	}
}


const vector<Vector>& Object::getNormalizedVertices(void) const { return (this -> xN); }

const vector<vector<int> >& Object::getIndexBuffer(void) const { return (this -> indexBuffer); }
