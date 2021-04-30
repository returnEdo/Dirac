#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DiracConstants.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"


namespace Dirac
{

class ScreenManager{

	private:

	GLFWwindow* mWindow;

	int mWidth;
	int mHeight;

	Vector mBackgroundColor	= Constants::BACKGROUND_COLOR;
	
	static std::unordered_map<int, int> mKeyState;
	static Vector2 mMousePosition;

	public:

	ScreenManager(int tWidth, int tHeight, const std::string& tTitle);
	ScreenManager(const std::string& tTitle);
	~ScreenManager(void);

	/* getters */
	inline GLFWwindow* getWindow(void)					{ return mWindow; }

	inline int getWidth(void)						const { return mWidth; }
	inline int getHeight(void)						const { return mHeight; }
	inline float getAspectRatio(void)					const { return (static_cast<float>(mWidth) / static_cast<float>(mHeight)); }

	static inline const std::unordered_map<int, int>& getKeyState(void) 	{ return ScreenManager::mKeyState; }
	static inline const Vector2& getMousePosition(void)			{ return ScreenManager::mMousePosition; }
	
	static inline bool isPressed(int key)					{ return (ScreenManager::mKeyState[key] == GLFW_PRESS); }
	static inline bool isReleased(int key)					{ return (ScreenManager::mKeyState[key] == GLFW_RELEASE); }
	static inline bool isHeldDown(int key)					{ return (ScreenManager::mKeyState[key] == GLFW_REPEAT); } 
	static inline bool isPressedOrHeld(int key)				{ return (ScreenManager::mKeyState[key] != GLFW_RELEASE); }

	/* setters */
	inline void wireframe(void)						const { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	inline void fill(void)							const { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
	inline void setBackgroundColor(const Vector& tBackgroundColor)		{ mBackgroundColor = tBackgroundColor; }


	/* callbacks */
	static void keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mode);
	static void mousePositionCallback(GLFWwindow* win, double xpos, double ypos);
	static void mouseButtonsCallback(GLFWwindow* win, int button, int action, int mode);

	/* utility */
	inline bool shouldRun(void) const					{ return (not glfwWindowShouldClose(mWindow)); }
	inline void shouldDie(void)						{ glfwSetWindowShouldClose(mWindow, true); }
	void clear(void);
	void update(void);
};

};
