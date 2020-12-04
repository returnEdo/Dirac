#pragma once

#include "Vector.h"
#include <array>
#include "Object.h"

using namespace std;


class Light{

	protected:

	Vector P; 	// light position
	array<double, 3> color;	// color of the light
	

	public:

	Light(const Vector& position = Vector(),
	      const array<double, 3>& colorr = {1.0, 1.0, 1.0}):
			P(position),
			color(colorr)		{}


	void updatePosition(const Vector& deltaPos){ this -> P += deltaPos; }
	void updateColor(const array<double, 3>& newColor)   { this -> color = newColor; }
	double getDistance2(const Vector& Q)	{ return norm2(this -> P - Q); }

	friend class Rasterizer;
};
