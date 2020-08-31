#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "renderer.h"

class InputManager
{
public:
	InputManager(Renderer* rend);

	void processInput(GLFWwindow* window);

private:
	Renderer* _renderer;
};