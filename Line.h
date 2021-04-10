#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>

#include "Buffers.h"
#include "Vector.h"
#include "Matrix.h"



class Line{

	private:

	std::unique_ptr<VertexArray>	vertexArray;
	std::unique_ptr<VertexBuffer>	vertexBuffer;
	std::unique_ptr<IndexBuffer>	indexBuffer;

	Vector color;
	float lineWidth	= 1.0f;

	public:

	Line(const Vector& a_, const Vector& b_, const Vector& color);

	/* setters */
	void setExtrema(const Vector& a_, const Vector& b_);
	inline void setColor(const Vector& color_)	{ color = color_; }
	inline void setLineWidth(float lineWidth_)	{ lineWidth = lineWidth_; }

	void render(Shader& shader);
	void updateUniforms(Shader& shader) const;
};
