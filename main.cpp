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
	
	/* programs that run on the GPU... */
	/* ...for objects... */
	Shader objectShader("resources/shaders/meshVertexShader.shader", "resources/shaders/meshFragmentShader.shader");
	
	Mesh object("resources/models/meshCube.dirac", Vector(), Matrix(Vector(1.0f, .0f, .0f),  .0f));

	Light light(Vector(10.0f));

	Camera camera(Vector(-5.0f, 5.0f, 5.0f), Matrix(Vector(.0f, 1.0f, .0f), .00f));
	camera.lookAt(Vector());
	
	float t = .0f;
	float dt = .03f;

	glEnable(GL_DEPTH_TEST);
	/* main loop */
	while (manager.shouldRun())
	{	

		t += dt;
		object.setAttitude(Matrix(Vector(.0f, 1.0f, .0f), t));
		
		/* connect the program */
		objectShader.bind();
		/* update camera data */
		camera.updateUniforms(objectShader);
		light.updateUniforms(objectShader);
		/* and finally draw */
		object.setPosition(Vector());
		object.render(objectShader);

		object.setPosition(Vector(.0f, 3.0f, .0f));
		object.render(objectShader);
		
		/* clears the screen and polls the events */
		manager.update();
		
		/* we can query the manager for the state of the buttons */
		if(Manager::isPressed(GLFW_KEY_ESCAPE))	{ manager.shouldDie();}

	}

	return 0;
}


