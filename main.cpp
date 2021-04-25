#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "ScreenManager.h"
#include "Shader.h"
#include "Manager.h"
#include "Renderer.h"
#include "TextureRenderer.h"
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
	
	// set system signature
	Dirac::Signature rendererSignature;
	rendererSignature.set(transformID, true);
	rendererSignature.set(colorID, true);

	Dirac::Signature textureRendererSignature;
	textureRendererSignature.set(transformID, true);
	textureRendererSignature.set(textureID, true);
	
	// create system
	gManager.setSignature<Renderer>(rendererSignature);
	std::shared_ptr<Renderer> pRenderer = gManager.getSystem<Renderer>();

	gManager.setSignature<TextureRenderer>(textureRendererSignature);
	std::shared_ptr<TextureRenderer> pTextureRenderer = gManager.getSystem<TextureRenderer>();

	// Initialize buffers
	pRenderer -> init();
	pTextureRenderer -> init("./resources/assets/textures/asteroid.png");

	// Create entities and add components

	EntityID id2 = gManager.createEntity();
	
	gManager.addComponent<Transform>(id2,
					 {
						 Vector(2.0f, .0f, 2.0f),
						 Matrix(Vector(0.0f, 1.0f, .0f), .0f),
						 Matrix(Vector(3.0f))
					 });

	gManager.addComponent<Texture>(id2,
				     {
					     Vector2(64.0f, .0f),

					     32.0f,
					     32.0f
				     });
	
	Transform& camera	= gManager.getComponent<Transform>(pRenderer -> mCameraID);

	camera.mPosition.y = 1.0f;
	camera.mAttitude = Matrix(Vector(1.0f, .0f, .0f), -.5f);


	Transform& spriteTransform = gManager.getComponent<Transform>(id2);

	spriteTransform.mShear *= .5f;

	float t = .0f;
	float dt = .005f;
	while (screenManager.shouldRun())
	{

		spriteTransform.mAttitude = Matrix(Vector(.0f, .0f, 1.0f), t);
		spriteTransform.mPosition = Vector(1.3f * cos(.33f * t), .0f, 1.3f * sin(.33f * t));
		t += dt;

		screenManager.clear();

		//pRenderer -> update();
		pTextureRenderer -> update(pRenderer -> mCameraID);

		screenManager.update();

		if (screenManager.isPressed(GLFW_KEY_ESCAPE))
		{
			screenManager.shouldDie();
		}
	}

	return 0;
}

