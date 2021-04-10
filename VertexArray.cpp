#include "VertexArray.h"
#include <iostream>


VertexArray::VertexArray(void){

	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}


VertexArray::~VertexArray(void){

	glDeleteVertexArrays(1, &id);
}


void VertexArray::bind(void) const{
	
	glBindVertexArray(id);
}


void VertexArray::unbind(void) const{

	glBindVertexArray(0);
}

void VertexArray::addAttribute(unsigned int count){
	/* adds new data format */
	/* type is assumed float */
	
	layouts.push_back({count, attributesStride});
	attributesStride += count * sizeof(float);
}

void VertexArray::enableAttributes(void) const{
	/* enables previous data formats */

	for (int i = 0; i < layouts.size(); i++){
		
		glVertexAttribPointer(i, layouts[i].count, GL_FLOAT, GL_FALSE, attributesStride, (void*)(layouts[i].startAt));
		glEnableVertexAttribArray(i);
	}
}
