//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "ScreenManager.h"
#include "Shader.h"
#include "Manager.h"
#include "DynamicBatchRenderer.h"
#include "RenderingComponents.h"
#include "Entity.h"


Dirac::Manager gManager;

using namespace Dirac;


int main()
{

	std::vector<Vertex> quadVertices =
	{
		{Vector(-.5f, -.5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
		{Vector(.5f, -.5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
		{Vector(.5f, .5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
		{Vector(-.5f, -.5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
		{Vector(.5f, .5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
		{Vector(-.5f, .5f, .0f), Vector(.0f, .0f, 1.0f), Vector(.2f, .5f, .2f)},
	};



	Dirac::ScreenManager screenManager("Dirac Demo");

	gManager.init();

	// get componenents ids
	unsigned int transformID	= gManager.getComponentID<Transform>();
	unsigned int colorID 		= gManager.getComponentID<Color>();
	unsigned int viewID 		= gManager.getComponentID<View>();
	unsigned int modelID 		= gManager.getComponentID<Model>();
	
	// set system signature
	Dirac::Signature rendererSignature;
	rendererSignature.set(transformID, true);
	rendererSignature.set(colorID, true);
	rendererSignature.set(modelID, true);
	
	// create system
	gManager.setSignature<DynamicBatchRenderer>(rendererSignature);
	std::shared_ptr<DynamicBatchRenderer> pBatchRenderer = gManager.getSystem<DynamicBatchRenderer>();

	// Initialize buffers
	pBatchRenderer -> DynamicBatchRenderer::init();

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

	gManager.addComponent<Model>(id1,
				     {
					     &quadVertices
				     });

	// Create entities and add components
	EntityID id2 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id2,
					 {
						 Vector(2.0f, 2.0f, .0f),
						 Matrix(Vector(1.0f, .0f, .0f), .0f),
						 Matrix(Vector(1.0f))
					 });

	gManager.addComponent<Color>(id2,
				     {
					     Vector(.3f, .3f, .7f),
					     1.0f
				     });

	gManager.addComponent<Model>(id2,
				     {
					     &quadVertices
				     });
	
	gManager.removeEntity(id2);

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
	Transform& transform 	= gManager.getComponent<Transform>(id1);
	Transform& camera	= gManager.getComponent<Transform>(cameraID);

	camera.mPosition.y = .8f;
	camera.mAttitude = Matrix(Vector(1.0f, .0f, .0f), -.3f);

	float t = 0.0f;
	float dt = 0.03f;

	while (screenManager.shouldRun())
	{

	//	transform.mShear	= Matrix(Vector(1.0f + .3f *sin(t), 1.0f, 1.0f));
		transform.mAttitude	= Matrix(Vector(1.0f, .0f, .0f), t);
	
		t += dt;

		screenManager.clear();

		pBatchRenderer -> DynamicBatchRenderer::update(cameraID);
		screenManager.update();

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
	}

	pBatchRenderer -> DynamicBatchRenderer::destroy();

	return 0;
}

