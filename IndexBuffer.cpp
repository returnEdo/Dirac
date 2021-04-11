#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indexData, const GPU_MODE& mode):
		count(indexData.size()){

	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned),
		     &indexData[0], (mode == GPU_MODE::STATIC? GL_STATIC_DRAW: GL_DYNAMIC_DRAW));
}


IndexBuffer::~IndexBuffer(void){

	glDeleteBuffers(1, &id);
}

void IndexBuffer::bind(void) const{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind(void) const{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void IndexBuffer::updateBufferData(const std::vector<unsigned>& indexData, unsigned int offset){

	bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, indexData.size() * sizeof(unsigned), &indexData[0]);
}
