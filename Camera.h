#pragma once

#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Object2.h"


#define DEFAULT_WIDTH 1200.0
#define DEFAULT_HEIGHT 800.0


class Camera{
	
	protected:
	
	Vector xCam;														// world position of the cam
	Vector thetaCam;													// orientation of the cam
	double phi;															// half fov y direction
	double W;
	double H;
	
	public:
	
	Camera(const Vector& xCam0, const Vector& thetaCam0, double p = M_PI / 3):
		xCam(xCam0),
		thetaCam(thetaCam0),
		phi(p),
		W(DEFAULT_WIDTH),
		H(DEFAULT_HEIGHT)						{}
	
	friend class Object;
	
	void changeFOV(double deltaTheta);
};


void Camera::changeFOV(double deltaPhi){
	
	this -> phi += deltaPhi;
}


