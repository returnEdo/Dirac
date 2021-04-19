#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DiracConstants.h"
#include "Vector.h"
#include "Vector2.h"

class ScreenManager{

	private:

	GLFWwindow* window;

	int width;
	int height;

	Vector backGroundColor	= Constants::BACKGROUND_COLOR;
	
	static std::unordered_map<int, int> keyState;
	static Vector2 mousePosition;

	public:

	ScreenManager(int width_, int height_, const std::string& title);
	ScreenManager(const std::string& title);
	~ScreenManager(void);

	/* getters */
	inline GLFWwindow* getWindow(void)					{ return window; }

	inline int getWidth(void)						const { return width; }
	inline int getHeight(void)						const { return height; }
	inline float getAspectRatio(void)					const { return (static_cast<float>(width) / static_cast<float>(height)); }

	static inline const std::unordered_map<int, int>& getKeyState(void) 	{ return ScreenManager::keyState; }
	static inline const Vector2& getMousePosition(void)			{ return ScreenManager::mousePosition; }
	
	static inline bool isPressed(int key)					{ return (ScreenManager::keyState[key] == GLFW_PRESS); }
	static inline bool isReleased(int key)					{ return (ScreenManager::keyState[key] == GLFW_RELEASE); }
	static inline bool isHeldDown(int key)					{ return (ScreenManager::keyState[key] == GLFW_REPEAT); } 

	/* setters */
	inline void wireframe(void)						const { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	inline void fill(void)							const { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
	inline void setBackgroundColor(const Vector& backGroundColor_)		{ backGroundColor = backGroundColor_; }


	/* callbacks */
	static void keyboardCallback(GLFWwindow* win, int key, int scancode, int action, int mode);
	static void mousePositionCallback(GLFWwindow* win, double xpos, double ypos);
	static void mouseButtonsCallback(GLFWwindow* win, int button, int action, int mode);

	/* utility */
	inline bool shouldRun(void) const					{ return (not glfwWindowShouldClose(window)); }
	inline void shouldDie(void)						{ glfwSetWindowShouldClose(window, true); }
	void clear(void);
	void update(void);
};
