#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "Buffers.h"
#include "Geometry.h"
#include "Camera.h"
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
	Shader lineShader("resources/shaders/lineVertexShader.shader", "resources/shaders/basicFragmentShader.shader");
	/* ...and for lines...*/
	Shader objectShader("resources/shaders/objectVertexShader.shader", "resources/shaders/basicFragmentShader.shader");
	
	Line line(Vector(-2.0f, -2.0f, .0f), Vector(2.0f, 2.0f, .0f), Vector(.7f, .2f, .2f));
	Object object("resources/models/square.dirac", Vector(), Matrix(Vector(1.0f, .0f, .0f),  .0f));

	Camera camera(Vector(.0f, .0f, 5.0f), Matrix(Vector(.0f, 1.0f, .0f), .00f));

	/* main loop */
	while (manager.shouldRun())
	{	
		
		/* connect the program */
		objectShader.bind();
		/* update camera data */
		camera.updateUniforms(objectShader);
		/* and finally draw */
		object.render(objectShader);
		
		/* same as above */
		lineShader.bind();
		camera.updateUniforms(lineShader);
		line.render(lineShader);
		
		/* clears the screen and polls the events */
		manager.update();
		
		/* we can query the manager for the state of the buttons */
		if(Manager::isPressed(GLFW_KEY_ESCAPE))	{ manager.shouldDie();}

		std::cout << manager.getMousePosition() << std::endl;

	}

	return 0;
}


