#include "ScreenManager.h"

#include <iostream>
#include <cassert>


std::unordered_map<int, int> ScreenManager::keyState;
Vector2 ScreenManager::mousePosition;


ScreenManager::ScreenManager(int width_, int height_, const std::string& title):
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
	glfwSetKeyCallback(window, ScreenManager::keyboardCallback);
	glfwSetMouseButtonCallback(window, ScreenManager::mouseButtonsCallback);
	glfwSetCursorPosCallback(window, ScreenManager::mousePositionCallback);

	glEnable(GL_DEPTH_TEST);
}


ScreenManager::ScreenManager(const std::string& title):
		ScreenManager(Constants::WINDOW_WIDTH,
			Constants::WINDOW_HEIGHT,
			title)	{}


ScreenManager::~ScreenManager(void){

	glfwTerminate();
}

void ScreenManager::clear(void){

	glClearColor(backGroundColor.x,
		     backGroundColor.y,
		     backGroundColor.z, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void ScreenManager::update(void){

	glfwSwapBuffers(window);
	glfwPollEvents();
}



void ScreenManager::keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mode){

	ScreenManager::keyState[key] = action;
}



void ScreenManager::mousePositionCallback(GLFWwindow* win, double xpos, double ypos){

	ScreenManager::mousePosition.x = static_cast<float>(xpos);
	ScreenManager::mousePosition.y = static_cast<float>(ypos);
}


void ScreenManager::mouseButtonsCallback(GLFWwindow* win, int button, int action, int mode){

	ScreenManager::keyState[button] = action;
}
