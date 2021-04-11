#pragma once

#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>

#include "Buffers.h"
#include "Vector.h"
#include "Matrix.h"

/* README:
   This class is optimised for multiple istances
   of the same objects */


struct IstanceGeometry{

	Vector position;
	Matrix attitude;
	Matrix shear;
};


class Tile{

	private:

	static std::unique_ptr<VertexArray>	vertexArray;
	static std::unique_ptr<VertexBuffer>	vertexBuffer;

	static std::vector<IstanceGeometry>	istancesGeometry;

	static unsigned int vertexCount;
	static unsigned int counter;

	unsigned int id;

	public:


	Tile(const std::string& address,
	     const Vector& position_,
	     const Matrix& attitude_,
	     const Matrix& shear_ = Matrix(Vector(1.0f)));

	Tile(const Vector& position_,
	     const Matrix& attitude_,
	     const Matrix& shear_ = Matrix(Vector(1.0f)));
	
	void render(Shader& shader, unsigned int primitive = GL_TRIANGLES);

	/* getters */
	inline const Vector& getPosition(void)	const { return Tile::istancesGeometry[id].position; }
	inline const Matrix& getAttitude(void)	const { return Tile::istancesGeometry[id].attitude; }
	inline const Matrix& getShear(void)	const { return Tile::istancesGeometry[id].shear; }
	inline unsigned int getVertexCount(void)const { return Tile::vertexCount; }
	inline unsigned int getId(void)		const { return id; }

	/* setters */
	inline void setPosition(const Vector& position_)	{ Tile::istancesGeometry[id].position = position_; }
	inline void setAttitude(const Matrix& attitude_)	{ Tile::istancesGeometry[id].attitude = attitude_; }
	inline void setShear(const Matrix& shear_)		{ Tile::istancesGeometry[id].shear = shear_; }
};

