#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const std::vector<float>& vertexData, const GPU_MODE& mode){
	/* reserve the buffers and stores it in the gpu */

	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float),
		     &vertexData[0], (mode == GPU_MODE::STATIC? GL_STATIC_DRAW: GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer(void){
	
	glDeleteBuffers(1, &id);
}


void VertexBuffer::bind(void) const{

	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind(void) const{

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VertexBuffer::updateBufferData(const std::vector<float>& vertexData, unsigned int offset){
	/* all the data is assumed to be replaced */

	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertexData.size() * sizeof(float), &vertexData[0]);
}
