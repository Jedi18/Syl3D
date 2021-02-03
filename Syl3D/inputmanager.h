#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "gui/guimanager.h"

class InputManager
{
public:
	InputManager(Renderer* rend, gui::GUIManager* guiManager);

	void processInput(GLFWwindow* window);

	void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
	static bool selectMode;

private:
	Renderer* _renderer;
	gui::GUIManager* _guiManager;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float lastX = 400;
	float lastY = 300;
	bool firstMouse = true;
};