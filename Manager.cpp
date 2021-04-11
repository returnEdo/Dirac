#include "Manager.h"

#include <iostream>
#include <cassert>


std::unordered_map<int, int> Manager::keyState;
Vector2 Manager::mousePosition;


Manager::Manager(int width_, int height_, const std::string& title):
		width(width_),
		height(height_) {
	/* initialize glfw */

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "\t...troubles creating GLFW window ..." << std::endl;
		glfwTerminate();
		assert(false);
	}
	glfwMakeContextCurrent(window);

	/* initialize Opengl function pointers */
	if (glewInit())
	{
		std::cout << "\t...troubles loading OpenGL function pointers..." << std::endl;
		assert(false);
	}

	/* set callback functions */
	glfwSetKeyCallback(window, Manager::keyboardCallback);
	glfwSetMouseButtonCallback(window, Manager::mouseButtonsCallback);
	glfwSetCursorPosCallback(window, Manager::mousePositionCallback);

	glEnable(GL_DEPTH_TEST);
}


Manager::Manager(const std::string& title):
		Manager(Constants::WINDOW_WIDTH,
			Constants::WINDOW_HEIGHT,
			title)	{}


Manager::~Manager(void){

	glfwTerminate();
}

void Manager::clear(void){

	glClearColor(backGroundColor.x,
		     backGroundColor.y,
		     backGroundColor.z, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Manager::update(void){

	glfwSwapBuffers(window);
	glfwPollEvents();
}



void Manager::keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mode){

	Manager::keyState[key] = action;
}



void Manager::mousePositionCallback(GLFWwindow* win, double xpos, double ypos){

	Manager::mousePosition.x = static_cast<float>(xpos);
	Manager::mousePosition.y = static_cast<float>(ypos);
}


void Manager::mouseButtonsCallback(GLFWwindow* win, int button, int action, int mode){

	Manager::keyState[button] = action;
}
