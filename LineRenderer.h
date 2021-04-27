#pragma once

#include "Entity.h"
#include "System.h"
#include "IRenderer.h"
#include "Shader.h"


namespace Dirac
{

struct ExtremumLayout
{
	float mPosition[3];
};

class LineRenderer: public ISystem, public IRenderer
{
	private:

	float mVertices[6];

	public:

	virtual void init(void) override;
	virtual void update(EntityID tCameraID) override;
	virtual void destroy(void) override;
};


};
