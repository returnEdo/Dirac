#pragma once

#include <vector>

#include "Entity.h"
#include "System.h"
#include "IRenderer.h"
#include "DiracConstants.h"
#include "RenderingComponents.h"


namespace Dirac
{

/*
SIGNATURE:
- Transform
- Color
- Model
*/

class DynamicBatchRenderer: public ISystem, public IRenderer
{
	public:

	virtual void init(void)	override;
	virtual void update(EntityID tCameraID) override;
	virtual void destroy(void) override;
};


};
