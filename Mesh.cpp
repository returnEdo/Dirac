#include "Mesh.h"

#include <fstream>
#include <iostream>

#include "DiracConstants.h"
#include "StringInput.h"


Mesh::Mesh(const std::vector<float>& vertexData,
	       const Vector& position_,
	       const Matrix& attitude_):
	       		position(position_),
			attitude(attitude_),
			vertexCount(vertexData.size() / 9){

	vertexArray 	= std::make_unique<VertexArray>();
	vertexBuffer	= std::make_unique<VertexBuffer>(vertexData);

	/* add position, normal and color attributes */
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::COLOR_COUNT);

	vertexArray -> enableAttributes();

	vertexArray -> unbind();
}


Mesh::Mesh(const std::string& address,
	   const Vector& position_,
	   const Matrix& attitude_):
	       		position(position_),
			attitude(attitude_)	{

	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	
	parseDirac(address, vertexData, indexData);

	vertexCount = vertexData.size() / 9;

	vertexArray 	= std::make_unique<VertexArray>();
	vertexBuffer	= std::make_unique<VertexBuffer>(vertexData);

	/* add position, normal and color attributes */
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::VERTICES_COUNT);
	vertexArray -> addAttribute(Constants::COLOR_COUNT);

	vertexArray -> enableAttributes();

}


void Mesh::render(Shader& shader, unsigned int primitive){
	/* bind program and vao*/

	shader.bind();
	updateUniforms(shader);

	vertexArray -> bind();
	
	glDrawArrays(primitive, 0, vertexCount);

}


void Mesh::updateUniforms(Shader& shader) const{

	shader.setUniform("uMeshPosition", position);
	shader.setUniform("uMeshAttitude", attitude);
	shader.setUniform("uMeshShear", shear);

}
