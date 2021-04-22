#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cmath>

#include "Shader.h"
#include "Manager.h"
#include "Renderer.h"
#include "RenderingComponents.h"
#include "Entity.h"

Dirac::Manager gManager;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


using namespace Dirac;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (glewInit())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

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
	gManager.setSignature<Renderer>(rendererSignature);
	std::shared_ptr<Renderer> pRenderer = gManager.getSystem<Renderer>();

	pRenderer -> init();

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
					     0.0f
				     });

	Color& color 		= gManager.getComponent<Color>(id1);
	Transform& transform 	= gManager.getComponent<Transform>(id1);
	Transform& camera	= gManager.getComponent<Transform>(pRenderer -> mCameraID);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	// render loop
	// -----------
	float dt = .05f;
	float t = .0f;
	while (!glfwWindowShouldClose(window))
	{

		color.mAlpha = std::max(static_cast<float>(.5f * (sin(t) + 1.0f)), .5f);
		transform.mShear = Matrix(Vector(1.0f)) * std::max(.5f, static_cast<float>(sin(2.0f * t)));
		transform.mPosition.x = .2f * cos(.2f * t);
		transform.mPosition.y = .2f * sin(.2f * t);

		camera.mPosition.x += dt;

		t += dt;
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		pRenderer -> update();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
