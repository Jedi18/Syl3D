#pragma once

#include <vector>
#include <memory>

#include "shader.h"
#include "texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"
#include "entity/cube.h"

#include "freecamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();

	void initialize();

	void render();

	FreeCamera _freeCamera;

private:
	Shader _shader;
	ShaderProgram _shaderProgram;
	TextureMaterial _texMaterial;
	std::vector<std::unique_ptr<entity::Cube>> _entities;
};