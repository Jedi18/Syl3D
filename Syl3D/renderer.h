#pragma once

#include "shader.h"

class Renderer
{
public:
	Renderer();

	void initialize();

	void render();

private:
	Shader _shader;
	ShaderProgram _shaderProgram;
	unsigned int _VAO;
};