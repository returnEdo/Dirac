#pragma once

#include <GL/glew.h>
#include <vector>

#include "VertexBuffer.h"


class IndexBuffer{

	private:

	unsigned int id;
	unsigned int count;

	public:

	IndexBuffer(const std::vector<unsigned int>& indexData, const GPU_MODE& mode = GPU_MODE::STATIC);
	~IndexBuffer(void);

	void bind(void) 	const;
	void unbind(void)	const;
	
	void updateBufferData(const std::vector<unsigned int>& indexData, unsigned int offset = 0);
	inline unsigned int getCount(void) const { return count; }
};
