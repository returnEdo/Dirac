#include "Line.h"

#include "DiracConstants.h"

Line::Line(const Vector& a_, const Vector& b_, const Vector& color_):
		color(color_) {
	
	std::vector<float> vertexData = {
		a_.x, a_.y, a_.z,
		b_.x, b_.y, b_.z
	};

	std::vector<unsigned int> indexData = {
		0, 1
	};
	
	vertexArray 	= std::make_unique<VertexArray>();
	vertexBuffer 	= std::make_unique<VertexBuffer>(vertexData);
	indexBuffer 	= std::make_unique<IndexBuffer>(indexData);

	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> enableAttributes();

	vertexArray -> unbind();
}


void Line::setExtrema(const Vector& a_, const Vector& b_){
	/* updates data in the vertexBuffer */

	std::vector<float> vertexData = {
		a_.x, a_.y, a_.z,
		b_.x, b_.y, b_.z
	};

	vertexArray -> bind();
	vertexBuffer -> updateBufferData(vertexData);
//	vertexArray -> unbind();
}


void Line::render(Shader& shader){
	/* draw call */

	shader.bind();
	updateUniforms(shader);

	vertexArray -> bind();

	glLineWidth(lineWidth);
	glDrawElements(GL_LINES, indexBuffer -> getCount(), GL_UNSIGNED_INT, nullptr);
}


void Line::updateUniforms(Shader& shader) const{

	shader.setUniform("uLineColor", color);
}


