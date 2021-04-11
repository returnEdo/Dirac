#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>
#include <array>

#include "Buffers.h"
#include "Vector.h"
#include "Matrix.h"

/* segments with batch rendering */

class Segment{

	private:
	
	static std::vector<float>  		vertexData;
	static std::vector<unsigned int>	indexData;

	static std::unique_ptr<VertexArray>	vertexArray;
	static std::unique_ptr<VertexBuffer>	vertexBuffer;
	static std::unique_ptr<IndexBuffer>	indexBuffer;

	float lineWidth	= 1.0f;

	static unsigned int counter;
	unsigned int id;

	public:

	Segment(const Vector& a, const Vector& b, const Vector& color);

	/* setters */
	void setExtrema(const Vector& a, const Vector& b);
	void setColor(const Vector& colorA, const Vector& colorB);
	inline void setColor(const Vector& color)	{ setColor(color, color); }
	inline void setLineWidth(float lineWidth_)	{ lineWidth = lineWidth_; }

	void render(Shader& shader);
};
