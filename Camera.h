#pragma once

#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Rotation.h"

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1920
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 1080
#endif


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
	void updatePosition(const Vector&);
	void updateAttitude(const Vector&);
};


void Camera::changeFOV(double deltaPhi){
	
	this -> phi += deltaPhi;
}

void Camera::updatePosition(const Vector& deltaVec){
	
	Rotation rot = Rotation(this -> thetaCam * (-1.0));

	this -> xCam += (rot * deltaVec);
}

void Camera::updateAttitude(const Vector& deltaTheta){

	this -> thetaCam += deltaTheta;
}
