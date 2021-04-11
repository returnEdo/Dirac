#include "Segment.h"

#include "DiracConstants.h"

#define EL_SEG (Constants::COLOR_COUNT + Constants::VERTICES_COUNT) * 2


std::vector<float> Segment::vertexData(6 * 2 * Constants::MAX_ISTANCES, .0f);
std::vector<unsigned int> Segment::indexData(2 * Constants::MAX_ISTANCES, 0);

std::unique_ptr<VertexArray>	Segment::vertexArray(nullptr);
std::unique_ptr<VertexBuffer>	Segment::vertexBuffer(nullptr);
std::unique_ptr<IndexBuffer>	Segment::indexBuffer(nullptr);

unsigned int Segment::counter = 0;



Segment::Segment(const Vector& a, const Vector& b, const Vector& color){


	/* update vertex buffer data */
	Segment::vertexData[Segment::counter * EL_SEG] 		= a.x;
	Segment::vertexData[Segment::counter * EL_SEG + 1] 	= a.y;
	Segment::vertexData[Segment::counter * EL_SEG + 2] 	= a.z;
	Segment::vertexData[Segment::counter * EL_SEG + 3] 	= color.x;
	Segment::vertexData[Segment::counter * EL_SEG + 4] 	= color.y;
	Segment::vertexData[Segment::counter * EL_SEG + 5] 	= color.z;
	Segment::vertexData[Segment::counter * EL_SEG + 6] 	= b.x;
	Segment::vertexData[Segment::counter * EL_SEG + 7] 	= b.y;
	Segment::vertexData[Segment::counter * EL_SEG + 8] 	= b.z;
	Segment::vertexData[Segment::counter * EL_SEG + 9] 	= color.x;
	Segment::vertexData[Segment::counter * EL_SEG + 10] 	= color.y;
	Segment::vertexData[Segment::counter * EL_SEG + 11] 	= color.z;

	/* update index buffer data */
	Segment::indexData[Segment::counter * 2] = Segment::counter * 2;
	Segment::indexData[Segment::counter * 2 + 1] = Segment::counter * 2 + 1;

	if (Segment::counter == 0){
		
		Segment::vertexArray 	= std::make_unique<VertexArray>();
		Segment::vertexBuffer 	= std::make_unique<VertexBuffer>(Segment::vertexData, GPU_MODE::DYNAMIC);
		Segment::indexBuffer 	= std::make_unique<IndexBuffer>(Segment::indexData);

		Segment::vertexArray -> addAttribute(Constants::VERTICES_COUNT);
		Segment::vertexArray -> addAttribute(Constants::COLOR_COUNT);
		Segment::vertexArray -> enableAttributes();

		vertexArray -> unbind();
	}


	id = Segment::counter;
	Segment::counter ++;
}


void Segment::setExtrema(const Vector& a, const Vector& b){
	/* updates data in the vertexBuffer */

	Segment::vertexData[id * EL_SEG] 	= a.x;
	Segment::vertexData[id * EL_SEG + 1] 	= a.y;
	Segment::vertexData[id * EL_SEG + 2] 	= a.z;
	Segment::vertexData[id * EL_SEG + 6] 	= b.x;
	Segment::vertexData[id * EL_SEG + 7] 	= b.y;
	Segment::vertexData[id * EL_SEG + 8] 	= b.z;
	
}


void Segment::setColor(const Vector& colorA, const Vector& colorB){

	Segment::vertexData[id * EL_SEG + 3] 	= colorA.x;
	Segment::vertexData[id * EL_SEG + 4] 	= colorA.y;
	Segment::vertexData[id * EL_SEG + 5] 	= colorA.z;
	Segment::vertexData[id * EL_SEG + 9] 	= colorB.x;
	Segment::vertexData[id * EL_SEG + 10] 	= colorB.y;
	Segment::vertexData[id * EL_SEG + 11] 	= colorB.z;
}


void Segment::render(Shader& shader){
	/* draw call */

	shader.bind();

	Segment::vertexArray -> bind();

	Segment::vertexBuffer -> updateBufferData(Segment::vertexData);
	Segment::indexBuffer -> updateBufferData(Segment::indexData);

	glLineWidth(lineWidth);
	glDrawElements(GL_LINES, 2 * Segment::counter, GL_UNSIGNED_INT, 0);
}

