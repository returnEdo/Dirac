#pragma once

#include <memory>
#include <iostream>
#include "Vector.h"
#include <GL/glut.h>
#include "Object.h"
#include "Camera.h"


#ifndef DELTA_MOVEMENT
#define DELTA_MOVEMENT .5
#endif


class Controller{

	public:
	
	shared_ptr<WorldSpace> wSpace;
	double deltaMov;
	bool cameraMode;

	Controller(WorldSpace& wSpacee):
		wSpace(shared_ptr<WorldSpace>(&wSpacee)),
		deltaMov(static_cast<double>(DELTA_MOVEMENT)),
		cameraMode(true)	{}


	void specialKeyFunction(unsigned char key, int x, int y);
	void specialKeyboardFunction(unsigned char key, int x, int y);
};


void Controller::specialKeyFunction(unsigned char key, int x, int y){
	/* Arrow control  */
	
	Vector deltaVec = Vector();
	
	switch(key){

		case (GLUT_KEY_RIGHT):

			if (this -> cameraMode){ deltaVec += Vector(.0, deltaMov, .0);}
			break;

		case (GLUT_KEY_LEFT):

			if (this -> cameraMode){ deltaVec -= Vector(.0, deltaMov, .0);}
			break;

		case (GLUT_KEY_UP):

			if (this -> cameraMode){ deltaVec += Vector(.0, .0, deltaMov);}
			break;

		case (GLUT_KEY_DOWN):

			if (this -> cameraMode){ deltaVec -= Vector(.0, .0, deltaMov);}
			break;
	}
	
	wSpace -> cam.updatePosition(deltaVec);
};



void Controller::specialKeyboardFunction(unsigned char key, int x, int y){


	Vector deltaVec = Vector();

	switch(key){

		case ('a'):

			if (this -> cameraMode){ deltaVec += Vector(deltaMov, .0, .0); }
			break;


		case ('d'):

			if (this -> cameraMode){ deltaVec -= Vector(deltaMov, .0, .0); }
			break;


		case ('s'):

			if (this -> cameraMode){ deltaVec += Vector(.0, deltaMov, .0); }
			break;


		case ('w'):

			if (this -> cameraMode){ deltaVec -= Vector(.0, deltaMov, .0); }
			break;

		case ('+'):

			if (this -> cameraMode){ wSpace -> cam.changeFOV(M_PI / 64); }
			break;

		case ('-'):

			if (this -> cameraMode){ wSpace -> cam.changeFOV(-M_PI / 64); }
			break;

		case ('q'):

			exit(0);
	}
	
	wSpace -> cam.updateAttitude(deltaVec);
}
