#pragma once

#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>

#include "Buffers.h"
#include "Vector.h"
#include "Matrix.h"

/* README:
   The difference with the object class is that:
   1) there is no index buffer;
   2) vertices in the vertex bufferare redundant
      to allow flat shading;
   So it should be used for small models */



class Mesh{

	protected:

	std::unique_ptr<VertexArray>	vertexArray;
	std::unique_ptr<VertexBuffer>	vertexBuffer;

	Vector position;
	Matrix attitude;				// local to world
	Matrix shear	= Matrix(Vector(1.0f));		// default identity

	unsigned int vertexCount;

	public:


	Mesh(const std::vector<float>& vertexData,
	     const Vector& position_,
	     const Matrix& attitude_);
	Mesh(const std::string& address,
	     const Vector& position_,
	     const Matrix& attitude_);
	
	virtual void render(Shader& shader, unsigned int primitive = GL_TRIANGLES);

	/* getters */
	inline const Vector& getPosition(void)	const { return position; }
	inline const Matrix& getAttitude(void)	const { return attitude; }
	inline const Matrix& getShear(void)	const { return shear; }
	inline unsigned int getVertexCount(void)const { return vertexCount; }

	/* setters */
	inline void setPosition(const Vector& position_)	{ position = position_; }
	inline void setAttitude(const Matrix& attitude_)	{ attitude = attitude_; }
	inline void setShear(const Matrix& shear_)		{ shear = shear_; }

	virtual void updateUniforms(Shader& shader) const;
};

