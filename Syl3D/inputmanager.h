#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class InputManager
{
public:
	InputManager();

	void processInput(GLFWwindow* window);
};