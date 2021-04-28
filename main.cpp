#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "ScreenManager.h"
#include "Shader.h"
#include "Manager.h"
#include "BatchLineRenderer.h"
#include "RenderingComponents.h"
#include "Entity.h"

#include "Vector.h"
#include "Vector2.h"
#include "Matrix.h"

Dirac::Manager gManager;

using namespace Dirac;


int main()
{

	Dirac::ScreenManager screenManager("Dirac Demo");

	gManager.init();

	// get componenents ids
	unsigned int transformID = gManager.getComponentID<Transform>();
	unsigned int colorID = gManager.getComponentID<Color>();
	unsigned int textureID = gManager.getComponentID<Texture>();
	unsigned int viewID = gManager.getComponentID<View>();
	unsigned int lineID = gManager.getComponentID<Line>();
	
	// set system signature
	Signature signature;

	signature.set(lineID, true);
	
	gManager.setSignature<BatchLineRenderer>(signature);
	std::shared_ptr<BatchLineRenderer> pBatchLineRenderer = gManager.getSystem<BatchLineRenderer>();


	// Initialize buffers
	pBatchLineRenderer -> BatchLineRenderer::init();

	// Create entities and add components

	EntityID id1 = gManager.createEntity();
	
	gManager.addComponent<Line>(id1,
					 {
						 {Vector(), Vector(.3f, .7f, .3f)},
						 {Vector(), Vector(.7f, .3f, .3f)}
					 });
	
	// Camera
	EntityID cameraID = gManager.createEntity();
	gManager.addComponent<Transform>(cameraID,
					 {	
						Vector(.0f, .0f, 5.0f),
						Matrix(Vector(.0f, 1.0f, .0f), .0f),
						Matrix()
					 });
	gManager.addComponent<View>(cameraID, {});


	auto& line = gManager.getComponent<Line>(id1);

	Transform& camera	= gManager.getComponent<Transform>(cameraID);

	camera.mPosition = Vector(0.0f, .0f, 4.0f);
	camera.mAttitude = Matrix(Vector(.0f, 1.0f, .0f), .0f);
	
	float t = .0f, dt = .1f;

	pBatchLineRenderer -> setLineWidth(5.0f);

	while (screenManager.shouldRun())
	{
		
		line.mVertexA.mPosition.x = 2.0f * cos(t);
		line.mVertexA.mPosition.y = 2.0f * sin(t);

		t += dt;

		screenManager.clear();

		pBatchLineRenderer -> BatchLineRenderer::update(cameraID);

		screenManager.update();

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
	}

	pBatchLineRenderer -> BatchLineRenderer::destroy();

	return 0;
}

