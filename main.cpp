#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "ScreenManager.hpp"
#include "Shader.hpp"
#include "Manager.hpp"
#include "BatchTextureRenderer.hpp"
#include "RenderingComponents.hpp"
#include "Entity.hpp"
#include "Clock.hpp"

#include "vec3.hpp"
#include "vec2.hpp"
#include "mat3.hpp"



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
	
	// set system signature
	Dirac::Signature textureRendererSignature;
	textureRendererSignature.set(transformID, true);
	textureRendererSignature.set(textureID, true);
	
	gManager.setSignature<BatchTextureRenderer>(textureRendererSignature);
	std::shared_ptr<BatchTextureRenderer> pBatchTextureRenderer = gManager.getSystem<BatchTextureRenderer>();

	// Initialize buffers
	pBatchTextureRenderer -> init("./resources/assets/textures/asteroid.png");

	// Create entities and add components

	EntityID id1 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id1,
					 {
						 Math::vec3(),
						 Math::mat3(Math::vec3(0.0f, 1.0f, .0f), .0f),
						 Math::mat3(Math::vec3(1.0f))
					 });

	gManager.addComponent<Texture>(id1,
				     {
					     Math::vec2(.0f, .0f),

					     32.0f,
					     32.0f,
					     1.0f
				     });
	
	EntityID id2 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id2,
					 {
						 Math::vec3(3.0f, 3.0f, .0f),
						 Math::mat3(Math::vec3(0.0f, 1.0f, .0f), .0f),
						 Math::mat3(Math::vec3(1.0f))
					 });

	gManager.addComponent<Texture>(id2,
				     {
					     Math::vec2(96.0f, .0f),

					     32.0f,
					     32.0f,
					     1.0f
				     });
	

	// Camera
	EntityID cameraID = gManager.createEntity();
	gManager.addComponent<Transform>(cameraID,
					 {	
						Math::vec3(.0f, .0f, 5.0f),
						Math::mat3(Math::vec3(.0f, 1.0f, .0f), .0f),
						Math::mat3()
					 });
	gManager.addComponent<View>(cameraID, {});
	Transform& camera	= gManager.getComponent<Transform>(cameraID);

	Texture& texture = gManager.getComponent<Texture>(id2);
	Transform& transform = gManager.getComponent<Transform>(id2);
	
	Physics::Clock clock;


	while (screenManager.shouldRun())
	{

		texture.mAlpha = (1.0f + sin(clock.timeSinceStartUp())) / 2.0f;
		transform.mPosition.x = 2.0f * sin(M_PI * clock.timeSinceStartUp());

		screenManager.clear();

		pBatchTextureRenderer -> update(cameraID);

		screenManager.update();

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
	}

	return 0;
}

