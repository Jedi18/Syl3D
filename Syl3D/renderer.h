#pragma once

#include "shader.h"
#include "texturematerial.h"

class Renderer
{
public:
	Renderer();

	void initialize();

	void render();

	// temp
	float vis;

private:
	Shader _shader;
	ShaderProgram _shaderProgram;
	TextureMaterial _texMaterial;
	unsigned int _VAO;
};