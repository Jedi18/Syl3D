#include "inputmanager.h"

InputManager::InputManager(Renderer* rend, gui::GUIManager* guiManager)
	:
	_renderer(rend),
	_guiManager(guiManager),
	selectMode(false)
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

	_renderer->_freeCamera->keyboardInput(deltaTime, zdir, xdir);
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	if (!selectMode) {
		float xoffset = (float)(xpos - lastX);
		float yoffset = (float)(lastY - ypos);
		lastX = (float)xpos;
		lastY = (float)ypos;

		_renderer->_freeCamera->mouseMovement(xoffset, yoffset);
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	_renderer->_freeCamera->mouseScrolled((float)xoffset, (float)yoffset);
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if (selectMode) {
			selectMode = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
		}
		else {
			selectMode = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (selectMode && !_guiManager->mouseOnGUI()) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			glm::vec3 mouseRay = _renderer->_mousePicker.calculateMouseRay(xpos, ypos);
			_renderer->mouseRayIntersections(math::Vec3(mouseRay.x, mouseRay.y, mouseRay.z));
		}
	}
}