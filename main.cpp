//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>

#include "ScreenManager.hpp"
#include "Shader.hpp"
#include "Manager.hpp"
#include "Entity.hpp"
#include "DynamicBatchRenderer.hpp"
#include "NarrowPhase.hpp"
#include "RenderingComponents.hpp"
#include "PhysicsComponents.hpp"
#include "Clock.hpp"


Dirac::Manager gManager;

using namespace Dirac;


int main()
{

	std::vector<Vertex> quadVertices =
	{
		{Math::vec3(-.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
		{Math::vec3(.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
		{Math::vec3(.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
		{Math::vec3(-.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
		{Math::vec3(.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
		{Math::vec3(-.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f)},
	};



	Dirac::ScreenManager screenManager("Dirac Demo");

	gManager.init();

	// get componenents ids
	unsigned int transformID	= gManager.getComponentID<Transform>();
	unsigned int colorID 		= gManager.getComponentID<Color>();
	unsigned int viewID 		= gManager.getComponentID<View>();
	unsigned int modelID 		= gManager.getComponentID<Model>();
	unsigned int boxID 		= gManager.getComponentID<Physics::AABB>();
	unsigned int inertiaID		= gManager.getComponentID<Physics::Inertia>();
	
	// set system signature
	Dirac::Signature rendererSignature;
	rendererSignature.set(transformID, true);
	rendererSignature.set(colorID, true);
	rendererSignature.set(modelID, true);
	
	// create system
	gManager.setSignature<DynamicBatchRenderer>(rendererSignature);
	std::shared_ptr<DynamicBatchRenderer> pBatchRenderer = gManager.getSystem<DynamicBatchRenderer>();

	// Initialize buffers
	pBatchRenderer -> init();

	// Create entities and add components
	EntityID id1 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id1,
					 {
						 Math::vec3(),
						 Math::mat3(Math::vec3(1.0f, .0f, .0f), .0f),
						 Math::mat3(Math::vec3(1.0f))
					 });

	gManager.addComponent<Color>(id1,
				     {
					     Math::vec3(.3f, .7f, .3f),
					     1.0f
				     });

	gManager.addComponent<Model>(id1,
				     {
					     &quadVertices
				     });
	
	gManager.addComponent<Physics::AABB>(id1, { Math::vec2(1.0f, 1.0f) });
	gManager.addComponent<Physics::Inertia>(id1, { 1.0f, 1.0f });
					


	// Create entities and add components
	EntityID id2 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id2,
					 {
						 Math::vec3(1.3f, 1.3f, .0f),
						 Math::mat3(Math::vec3(1.0f, .0f, .0f), .0f),
						 Math::mat3(Math::vec3(1.0f))
					 });

	gManager.addComponent<Color>(id2,
				     {
					     Math::vec3(.7f, .3f, .3f),
					     1.0f
				     });

	gManager.addComponent<Model>(id2,
				     {
					     &quadVertices
				     });
	
	gManager.addComponent<Physics::AABB>(id2, { Math::vec2(1.0f, 1.0f) });
	gManager.addComponent<Physics::Inertia>(id2, { 1.0f, 1.0f });

	// Camera
	EntityID cameraID = gManager.createEntity();
	gManager.addComponent<Transform>(cameraID,
					 {	
						Math::vec3(.0f, .0f, 5.0f),
						Math::mat3(Math::vec3(.0f, 1.0f, .0f), .0f),
						Math::mat3()
					 });
	gManager.addComponent<View>(cameraID, {});


	
	// Get compoenent references to play with
	Transform& transform 	= gManager.getComponent<Transform>(id1);
	Transform& camera	= gManager.getComponent<Transform>(cameraID);

	Color& color1		= gManager.getComponent<Color>(id1);
	Color& color2		= gManager.getComponent<Color>(id2);


	Physics::Clock clock;

	float dx = 0.03f;
	Physics::CollisionInfo lCollisionInfo;
	lCollisionInfo.mEntityA = id1;
	lCollisionInfo.mEntityB = id2;

	while (screenManager.shouldRun())
	{

		screenManager.clear();

		pBatchRenderer -> update(cameraID);
		screenManager.update();

		lCollisionInfo.mCollision = false;
		Physics::checkCollision(lCollisionInfo);

		if (lCollisionInfo.mCollision)
		{
			Physics::solvePenetration(lCollisionInfo);
			color1.mColor = Math::vec3(.3f, .3f, .7f);	
			color2.mColor = Math::vec3(.3f, .3f, .7f);	

		}
		else
		{
			color1.mColor = Math::vec3(.3f, .7f, .3f);	
			color2.mColor = Math::vec3(.7f, .3f, .3f);	
		}

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_UP))		{ transform.mPosition.y += dx; }
		if (screenManager.isPressedOrHeld(GLFW_KEY_DOWN))	{ transform.mPosition.y -= dx; }
		if (screenManager.isPressedOrHeld(GLFW_KEY_RIGHT))	{ transform.mPosition.x += dx; }
		if (screenManager.isPressedOrHeld(GLFW_KEY_LEFT))	{ transform.mPosition.x -= dx; }

		PRINT_AUTO(clock.refreshTimer());
	}

	PRINT_AUTO(clock.timeSinceStartUp());

	return 0;
}

