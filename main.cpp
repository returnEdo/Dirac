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
#include "Integrator.hpp"
#include "RenderingComponents.hpp"
#include "PhysicsComponents.hpp"
#include "Clock.hpp"


Dirac::Manager gManager;

using namespace Dirac;


int main()
{

	std::vector<Vertex> quadVertices =
	{
		{Math::vec3(-.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
		{Math::vec3(.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
		{Math::vec3(.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
		{Math::vec3(-.5f, -.5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
		{Math::vec3(.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
		{Math::vec3(-.5f, .5f, .0f), Math::vec3(.0f, .0f, 1.0f), Math::vec3(.2f, .5f, .2f), 1.0f},
	};



	Dirac::ScreenManager screenManager("Dirac Demo");

	gManager.init();

	// get componenents ids
	unsigned int transformID	= gManager.getComponentID<Transform>();
	unsigned int colorID 		= gManager.getComponentID<Color>();
	unsigned int viewID 		= gManager.getComponentID<View>();
	unsigned int modelID 		= gManager.getComponentID<Model>();
	unsigned int inertiaID		= gManager.getComponentID<Physics::Inertia>();
	unsigned int forcesID		= gManager.getComponentID<Physics::Forces>();
	unsigned int dynamicsID		= gManager.getComponentID<Physics::Dynamics>();
	
	// set system signature
	Dirac::Signature rendererSignature;
	rendererSignature.set(transformID, true);
	rendererSignature.set(colorID, true);
	rendererSignature.set(modelID, true);

	Signature integratorSignature;
	integratorSignature.set(inertiaID);
	integratorSignature.set(forcesID);
	integratorSignature.set(transformID);
	integratorSignature.set(dynamicsID);
	
	// create system
	gManager.setSignature<DynamicBatchRenderer>(rendererSignature);
	std::shared_ptr<DynamicBatchRenderer> pBatchRenderer = gManager.getSystem<DynamicBatchRenderer>();

	gManager.setSignature<Physics::Integrator>(integratorSignature);

	std::shared_ptr<Physics::Integrator> pIntegrator = gManager.getSystem<Physics::Integrator>();

	// Initialize buffers
	pBatchRenderer -> init();

	// Create entities and add components
	EntityID id1 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id1,
					 {
						 Math::vec3(),
						 Math::Rotor(0.0f, Math::vec3(0.0f, 1.0f, 0.0f)),
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
	
	gManager.addComponent<Physics::Dynamics>(id1, {Math::vec3(), Math::vec3()});
	gManager.addComponent<Physics::Forces>(id1, {Math::vec3(), Math::vec3(), 2.0f, 2.0f});
	gManager.addComponent<Physics::Inertia>(id1, { 1.0f, Math::mat3(Math::vec3(1.0f, 1.0f, 1.0f)) });
					


	// Camera
	EntityID cameraID = gManager.createEntity();
	gManager.addComponent<Transform>(cameraID,
					 {	
						Math::vec3(.0f, .0f, 5.0f),
						Math::Rotor(0.0f, Math::vec3(.0f, 1.0f, .0f)),
						Math::mat3()
					 });
	gManager.addComponent<View>(cameraID, {});


	
	// Get compoenent references to play with
	Transform& transform 	= gManager.getComponent<Transform>(id1);
	Physics::Forces& forces = gManager.getComponent<Physics::Forces>(id1);
	Transform& camera	= gManager.getComponent<Transform>(cameraID);
	Color& color1		= gManager.getComponent<Color>(id1);


	Physics::Clock clock;
	clock.refreshTimer();

	float dx = 0.03f;
	
	while (screenManager.shouldRun())
	{

		screenManager.clear();

		pIntegrator 	-> update(clock.refreshTimer());
		pBatchRenderer 	-> update(cameraID);

		screenManager.update();

		if (screenManager.isPressedOrHeld(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_RIGHT))
		{
			forces.mTorque = Math::vec3(10.0f, 10.0f, 0.0f);
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_LEFT))
		{
			forces.mTorque = Math::vec3(-10.0f, -10.0f, 0.0f);
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_UP))
		{
			forces.mForce = Math::vec3(0.0f, 10.0f, 0.0f);
		}
		if (screenManager.isPressedOrHeld(GLFW_KEY_DOWN))
		{
			forces.mForce = Math::vec3(0.0f, -10.0f, 0.0f);
		}
	}

	return 0;
}

