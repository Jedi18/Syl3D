#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "inputmanager.h"
#include "renderer.h"

class Application
{
public:
	Application();

	/**
	* Initialize the glfw window
	*/
	bool initialize();

	/**
	* Run the program loop
	*/
	void run();

private:
	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	GLFWwindow* _window;
	Renderer _renderer;
	InputManager _inputManager;

	static const int INIT_WINDOW_WIDTH;
	static const int INIT_WINDOW_HEIGHT;
	static const char* INIT_WINDOW_TITLE;
};