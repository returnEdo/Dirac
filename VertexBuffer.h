#pragma once

#include <GL/glew.h>
#include <vector>


enum class GPU_MODE{

	STATIC,
	DYNAMIC
};



class VertexBuffer{

	private:

	unsigned int id;

	public:

	VertexBuffer(const std::vector<float>& vertexData, const GPU_MODE& mode = GPU_MODE::STATIC);
	~VertexBuffer(void);	

	void bind(void)		const;
	void unbind(void)	const;

	void updateBufferData(const std::vector<float>& vertexData, unsigned int offset = 0);
};

