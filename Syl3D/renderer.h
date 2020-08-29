#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "shader.h"

class Renderer
{
public:
	Renderer();

	void initialize();

	void render();

private:
	Shader _shader;
	GLuint _shaderProgram;
};