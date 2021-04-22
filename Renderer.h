#pragma once

#include <memory>

#include "Entity.h"
#include "System.h"
#include "Shader.h"


namespace Dirac
{


class Renderer: public ISystem
{
	private:

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	Shader* mShader { nullptr };

	public:
	
	// public access to the camera
	EntityID mCameraID;

	~Renderer(void);

	void init(void);
	void update(void);
};


};
