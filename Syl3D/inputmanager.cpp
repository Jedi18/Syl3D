#include "inputmanager.h"

InputManager::InputManager(Renderer* rend) 
	:
	_renderer(rend)
{}

void InputManager::processInput(GLFWwindow* window) {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

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

	const float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_renderer->cameraPos += cameraSpeed * _renderer->cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		_renderer->cameraPos -= cameraSpeed * _renderer->cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		_renderer->cameraPos -= glm::normalize(glm::cross(_renderer->cameraFront, _renderer->cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		_renderer->cameraPos += glm::normalize(glm::cross(_renderer->cameraFront, _renderer->cameraUp)) * cameraSpeed;
	}
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	_renderer->yaw += xoffset;
	_renderer->pitch += yoffset;

	if (_renderer->pitch > 89.0f) {
		_renderer->pitch = 89.0f;
	}

	if (_renderer->pitch < -89.0f) {
		_renderer->pitch = -89.0f;
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	_renderer->_zoom -= (float)yoffset;

	if (_renderer->_zoom < 1.0f) {
		_renderer->_zoom = 1.0f;
	}
	if (_renderer->_zoom > 45.0f) {
		_renderer->_zoom = 45.0f;
	}
}