#include "inputmanager.h"

InputManager::InputManager(Renderer* rend) 
	:
	_renderer(rend)
{}

void InputManager::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		_renderer->vis += 0.0005f;
		if (_renderer->vis >= 1.0f) {
			_renderer->vis = 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		_renderer->vis -= 0.0005f;
		if (_renderer->vis <= 0.0f) {
			_renderer->vis = 0.0f;
		}
	}
}