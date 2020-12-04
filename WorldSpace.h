#pragma once

#include <iostream>
#include <memory>
#include "Camera.h"
#include "Object.h"
#include "Rasterizer.h"
#include "Light.h"


class WorldSpace{

	protected:

	Camera cam;
	vector<shared_ptr<Object> > objectPtrs;
	shared_ptr<Light> light;		/* TODO:	 will become a vector  */

	Rasterizer rast;

	public:

	WorldSpace(void):
		cam(Camera(Vector(.0, .0, -5.0),
			   Vector()))	{}
	
	void addObject(Object& newObj);
	void addLight(Light& newLight);
	void updateVertices(void);

	void rasterize(void);
	void render(void);
	
	friend class Controller;

};



void WorldSpace::addObject(Object& newObj){

	(this -> objectPtrs).emplace_back(&newObj);
}


void WorldSpace::addLight(Light& newLight){

	this -> light = shared_ptr<Light>(&newLight);
}



void WorldSpace::updateVertices(void){
	/* updates the vertices of all the object of the world  */
	for (auto &obj: this -> objectPtrs){

		obj -> updateVertices(this -> cam);
	}
}


void WorldSpace::rasterize(void){
	/* updates the depth and frame buffers  */

	for (auto& obj: objectPtrs){

		rast.rasterizeObject(obj, this -> light);
	}
}



void WorldSpace::render(void){
	/* Draws on screen  */
	
	this -> rasterize();

	rast.paintCanvas();
}


