#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Shader.h"
#include "DiracConstants.h"



class Camera{

	protected:

	Vector position;
	Matrix attitude;		// cam to world matrix

	/* projections settings */
	float deltax		= Constants::DELTAX;
	float deltaz		= Constants::DELTAZ;
	float near		= Constants::NEAR_PLANE;
	float aspectRatio 	= Constants::ASPECT_RATIO;


	public:

	Camera(const Vector& position_, const Matrix& attitude_ = Matrix(Vector(1.0f, .0f, .0f), .0f));

	/* getters */
	inline const Vector& getPosition(void) const { return position; }
	inline const Matrix& getAttitude(void) const { return attitude; }

	/* setters */
	inline void setPosition(const Vector& position_) 	{ position = position_; }
	inline void setAttitude(const Matrix& attitude_)	{ attitude = attitude_; }
	inline void setAspectRatio(float aspectRatio_)		{ aspectRatio = aspectRatio_; }	
	inline void setDeltaX(float deltax_)			{ deltax = deltax_; }

	void lookAt(const Vector& x);

	virtual void updateUniforms(Shader& shader) const;
};
