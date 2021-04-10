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
	Manager manager("Dirac Demo");

	Shader lineShader("resources/shaders/lineVertexShader.shader", "resources/shaders/basicFragmentShader.shader");
	Shader objectShader("resources/shaders/objectVertexShader.shader", "resources/shaders/basicFragmentShader.shader");

	Line line(Vector(-2.0f, -2.0f, .0f), Vector(2.0f, 2.0f, .0f), Vector(.7f, .2f, .2f));
	Object object("resources/models/square.dirac", Vector(), Matrix(Vector(1.0f, .0f, .0f),  .0f));

	Camera camera(Vector(.0f, .0f, 5.0f), Matrix(Vector(.0f, 1.0f, .0f), .00f));


	float t = .0f;
	float dt = .02f;
	float r = .2f;
	// render loop
	while (manager.shouldRun())
	{	
		t += dt;

		objectShader.bind();
		camera.updateUniforms(objectShader);
		object.updateUniforms(objectShader);
		object.render(objectShader);
		
		lineShader.bind();
		camera.updateUniforms(lineShader);
		line.render(lineShader);


		manager.update();

		if (Manager::isPressed(GLFW_KEY_SPACE)){

			std::cout << "space" << std::endl;
		}
		else if(Manager::isPressed(GLFW_KEY_ESCAPE))	{ manager.shouldDie();}

	}

	return 0;
}


