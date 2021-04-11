#pragma once

#include "Vector.h"
#include "Shader.h"

class Light{

	protected:

	Vector position;

	public:

	Light(const Vector& position_);

	/* setters */
	inline void setPosition(const Vector& position_)	{ position = position_; }

	/* getters */
	inline const Vector& getPosition(void)	const		{ return position; }

	void updateUniforms(Shader& shader) const;
};
