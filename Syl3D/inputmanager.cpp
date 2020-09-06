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

	float zdir = 0;
	float xdir = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		zdir += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		zdir -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		xdir -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		xdir += 1;
	}

	_renderer->_freeCamera.keyboardInput(deltaTime, zdir, xdir);
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos);
	lastX = (float)xpos;
	lastY = (float)ypos;

	_renderer->_freeCamera.mouseMovement(xoffset, yoffset);
	//glm::vec3 mouseRay = _renderer->_mousePicker.calculateMouseRay(xoffset, yoffset);
	//std::cout << "(" << mouseRay.x << ", " << mouseRay.y << ", " << mouseRay.z << ")\n";
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	_renderer->_freeCamera.mouseScrolled((float)xoffset, (float)yoffset);
}