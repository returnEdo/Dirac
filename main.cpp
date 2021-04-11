#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "Buffers.h"
#include "Geometry.h"
#include "Camera.h"
#include "Light.h"
#include "Manager.h"
#include "DiracConstants.h"

#include "Vector2.h"
#include "Vector.h"
#include "Matrix.h"

int main()
{
	/* window manager */
	Manager manager("Dirac Demo");
	
	Shader objectShader("resources/shaders/segmentVertexShader.shader", "resources/shaders/basicFragmentShader.shader");
	
	Segment seg1(Vector(-1.0f, .0f, .0f), Vector(1.0f, .0f, .0f), Vector(1.0f, .0f, .0f));
	Segment seg2(Vector(1.0f, .0f, .0f), Vector(1.0f, 1.0f, .0f), Vector(.0f, 1.0f, .0f));

	Light light(Vector(10.0f));

	Camera camera(Vector(.0f, .0f, 5.0f), Matrix(Vector(.0f, 1.0f, .0f), .00f));
	camera.lookAt(Vector());
	
	float t = .0f;
	float dt = .03f;

	/* main loop */
	while (manager.shouldRun())
	{	
		manager.clear();

		t += dt;

		seg2.setExtrema(Vector(1.0f, .0f, .0f), Vector(1.0f + .2f * sin(t), 1.0f + .2 * cos(t), .0f));
		
		objectShader.bind();
		camera.updateUniforms(objectShader);
		//light.updateUniforms(objectShader);
		seg1.render(objectShader);
		
		manager.update();
		
		if(Manager::isPressed(GLFW_KEY_ESCAPE))	{ manager.shouldDie();}

	}

	return 0;
}


