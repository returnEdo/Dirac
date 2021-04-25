#include "ScreenManager.h"

#include <iostream>
#include <cassert>

#include "DiracMacros.h"

namespace Dirac
{

std::unordered_map<int, int> ScreenManager::mKeyState;
Vector2 ScreenManager::mMousePosition;


ScreenManager::ScreenManager(int tWidth, int tHeight, const std::string& tTitle):
		mWidth(tWidth),
		mHeight(tHeight) {
	// Create window

	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	mWindow = glfwCreateWindow(mWidth, mHeight, tTitle.c_str(), NULL, NULL);
	if (mWindow == NULL)
	{
		glfwTerminate();
		DIRAC_ASSERT(false, "Could not create GLFW window!!");
	}
	glfwMakeContextCurrent(mWindow);

	// Load opengl functions pointers
	if (glewInit())
	{
		DIRAC_ASSERT(false, "Could not load OpenGL function pointers!!");
	}

	// Set callback functions
	glfwSetKeyCallback(mWindow, ScreenManager::keyboardCallback);
	glfwSetMouseButtonCallback(mWindow, ScreenManager::mouseButtonsCallback);
	glfwSetCursorPosCallback(mWindow, ScreenManager::mousePositionCallback);

	// Blending to allow for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}


ScreenManager::ScreenManager(const std::string& tTitle):
		ScreenManager(Constants::WINDOW_WIDTH,
			Constants::WINDOW_HEIGHT,
			tTitle)	{}


ScreenManager::~ScreenManager(void){

	glfwTerminate();
}

void ScreenManager::clear(void){

	glClearColor(mBackgroundColor.x,
		     mBackgroundColor.y,
		     mBackgroundColor.z, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void ScreenManager::update(void){

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}



void ScreenManager::keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mode){

	ScreenManager::mKeyState[key] = action;
}



void ScreenManager::mousePositionCallback(GLFWwindow* win, double xpos, double ypos){

	ScreenManager::mMousePosition.x = static_cast<float>(xpos);
	ScreenManager::mMousePosition.y = static_cast<float>(ypos);
}


void ScreenManager::mouseButtonsCallback(GLFWwindow* win, int button, int action, int mode){

	ScreenManager::mKeyState[button] = action;
}


};
