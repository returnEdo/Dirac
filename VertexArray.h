#pragma once

#include <GL/glew.h>
#include <vector>


class Layout{

	public:

	unsigned int count;
	unsigned int startAt;
};


class VertexArray{

	private:

	unsigned int id;
	unsigned int attributesStride	= 0;
	std::vector<Layout>	layouts;

	public:

	VertexArray(void);
	~VertexArray(void);

	void bind(void) const;
	void unbind(void) const;

	void addAttribute(unsigned int count);
	void enableAttributes(void) const;
};
