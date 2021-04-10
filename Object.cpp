#include "Object.h"

#include <fstream>
#include <iostream>

#include "DiracConstants.h"
#include "StringInput.h"


Object::Object(const std::vector<float>& vertexData,
	       const std::vector<unsigned int>& indexData,
	       const Vector& position_,
	       const Matrix& attitude_):
	       		position(position_),
			attitude(attitude_)	{

	vertexArray 	= std::make_unique<VertexArray>();
	vertexBuffer	= std::make_unique<VertexBuffer>(vertexData);
	indexBuffer 	= std::make_unique<IndexBuffer>(indexData);

	/* add position and color attributes */
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::COLOR_COUNT);

	vertexArray -> enableAttributes();

	vertexArray -> unbind();
}


Object::Object(const std::string& address,
	       const Vector& position_,
	       const Matrix& attitude_):
	       		position(position_),
			attitude(attitude_)	{

	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	
	parseDirac(address, vertexData, indexData);

	vertexArray 	= std::make_unique<VertexArray>();
	vertexBuffer	= std::make_unique<VertexBuffer>(vertexData);
	indexBuffer 	= std::make_unique<IndexBuffer>(indexData);

	/* add position and color attributes */
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::COLOR_COUNT);

	vertexArray -> enableAttributes();

}


void Object::render(Shader& shader, unsigned int primitive){
	/* bind program and vao*/

	shader.bind();
	updateUniforms(shader);

	vertexArray -> bind();
	
	glDrawElements(primitive, indexBuffer -> getCount(), GL_UNSIGNED_INT, 0);
}


void Object::updateUniforms(Shader& shader) const{

	shader.setUniform("uObjectPosition", position);
	shader.setUniform("uObjectAttitude", attitude);
	shader.setUniform("uObjectShear", shear);

}
