#pragma once

#include "shader.h"
#include "texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"

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
	entity::Rectangle* _rectangle;
	entity::Triangle* _triangle;
};