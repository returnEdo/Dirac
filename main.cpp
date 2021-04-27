//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "ScreenManager.h"
#include "Shader.h"
#include "Manager.h"
#include "MeshRenderer.h"
#include "RenderingComponents.h"
#include "Entity.h"


Dirac::Manager gManager;

using namespace Dirac;


int main()
{

	Dirac::ScreenManager screenManager("Dirac Demo");

	gManager.init();

	// get componenents ids
	unsigned int transformID = gManager.getComponentID<Transform>();
	unsigned int colorID = gManager.getComponentID<Color>();
	unsigned int viewID = gManager.getComponentID<View>();
	
	// set system signature
	Dirac::Signature rendererSignature;
	rendererSignature.set(transformID, true);
	rendererSignature.set(colorID, true);
	
	// create system
	gManager.setSignature<MeshRenderer>(rendererSignature);
	std::shared_ptr<MeshRenderer> pMeshRenderer = gManager.getSystem<MeshRenderer>();

	// Initialize buffers
	pMeshRenderer -> MeshRenderer::init();

	// Create entities and add components
	EntityID id1 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id1,
					 {
						 Vector(),
						 Matrix(Vector(1.0f, .0f, .0f), .0f),
						 Matrix(Vector(1.0f))
					 });

	gManager.addComponent<Color>(id1,
				     {
					     Vector(.3f, .7f, .3f),
					     1.0f
				     });
	
	EntityID id2 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id2,
					 {
						 Vector(),
						 Matrix(Vector(0.0f, 1.0f, .0f), M_PI_4),
						 Matrix(Vector(3.0f))
					 });

	gManager.addComponent<Color>(id2,
				     {
					     Vector(.7f, .3f, .3f),
					     1.0f
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


	
	// Get compoenent references to play with
	Color& color 		= gManager.getComponent<Color>(id2);
	Transform& transform 	= gManager.getComponent<Transform>(id1);
	Transform& camera	= gManager.getComponent<Transform>(cameraID);

	camera.mPosition.y = .8f;
	camera.mAttitude = Matrix(Vector(1.0f, .0f, .0f), -.3f);

	float dt = .05f;
	float t = .0f;
	while (screenManager.shouldRun())
	{

		screenManager.clear();

		transform.mAttitude = Matrix(Vector(.0f, .0f, 1.0f), t);

		t += dt;


		pMeshRenderer -> MeshRenderer::update(cameraID);
		screenManager.update();

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_UP))
		{
			color.mAlpha += .005f;
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_DOWN))
		{
			color.mAlpha -= .005f; 
		}
	}

	pMeshRenderer -> MeshRenderer::destroy();

	return 0;
}

