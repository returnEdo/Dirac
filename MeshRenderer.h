#pragma once

#include <memory>

#include "Entity.h"
#include "System.h"
#include "IRenderer.h"
#include "Shader.h"


namespace Dirac
{


class MeshRenderer:  public ISystem, public IRenderer
{
	public:
	
	virtual void init(void) override;
	virtual void update(EntityID tCameraID) override; 
	virtual void destroy(void) override;
};


};
