#pragma once

#include "Entity.h"
#include "System.h"
#include "IRenderer.h"
#include "RenderingComponents.h"


namespace Dirac
{


class BatchLineRenderer: public ISystem, public IRenderer
{
	private:
	
	float mLineWidth = 1.0f;

	public:

	virtual void init(void) override;
	virtual void update(EntityID tCameraID) override;
	virtual void destroy(void) override;

	inline void setLineWidth(float tLineWidth) 	{ mLineWidth = tLineWidth; } 
};


};
