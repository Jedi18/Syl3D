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

private:
	GLFWwindow* _window;
	InputManager _inputManager;
	Renderer _renderer;

	static const int INIT_WINDOW_WIDTH;
	static const int INIT_WINDOW_HEIGHT;
	static const char* INIT_WINDOW_TITLE;
};