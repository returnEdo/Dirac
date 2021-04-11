#include "Tile.h"

#include <fstream>
#include <iostream>

#include "DiracConstants.h"
#include "StringInput.h"

#ifndef TILE_H
#define TILE_H

std::unique_ptr<VertexArray>	Tile::vertexArray(nullptr);
std::unique_ptr<VertexBuffer>	Tile::vertexBuffer(nullptr);

std::vector<IstanceGeometry>	Tile::istancesGeometry = {};

unsigned int Tile::vertexCount 	= 0;
unsigned int Tile::counter	= 0;

#endif

Tile::Tile(const std::string& address,
	   const Vector& position_,
	   const Matrix& attitude_,
	   const Matrix& shear_){
	
	/* @ the first instanciation set up the buffers */
	if (Tile::counter == 0){

		std::vector<float> vertexData;
		std::vector<unsigned int> indexData;
		
		parseDirac(address, vertexData, indexData);

		Tile::vertexCount = vertexData.size() / 9;

		Tile::vertexArray 	= std::make_unique<VertexArray>();
		Tile::vertexBuffer	= std::make_unique<VertexBuffer>(vertexData);

		/* add position, normal and color attributes */
		Tile::vertexArray -> addAttribute(Constants::VERTICES_COUNT);
		Tile::vertexArray -> addAttribute(Constants::VERTICES_COUNT);
		Tile::vertexArray -> addAttribute(Constants::COLOR_COUNT);

		Tile::vertexArray -> enableAttributes();

	}
	/* update the uniforms */
	Tile::istancesGeometry.push_back({position_, attitude_, shear_});
	
	id = counter;
	
	Tile::counter ++;
}


Tile::Tile(const Vector& position_,
     	   const Matrix& attitude_,
     	   const Matrix& shear_){

	Tile::istancesGeometry.push_back({position_, attitude_, shear_});
	
	id = counter;
	
	Tile::counter ++;
}


void Tile::render(Shader& shader, unsigned int primitive){
	/* the render pass renderes all the tiles */

	shader.bind();
	vertexArray -> bind();

	for (int i = 0; i < Tile::istancesGeometry.size(); i++){

		shader.setUniform("uMeshPosition", Tile::istancesGeometry[i].position);
		shader.setUniform("uMeshAttitude", Tile::istancesGeometry[i].attitude);
		shader.setUniform("uMeshShear", Tile::istancesGeometry[i].shear);

		glDrawArrays(primitive, 0, Tile::vertexCount);
	}
}

