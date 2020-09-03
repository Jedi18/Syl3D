#pragma once

#include <vector>
#include <memory>

#include "shader.h"
#include "texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"
#include "entity/cube.h"
#include "entity/uvsphere.h"
#include "entity/icosphere.h"

#include "freecamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();

	void initialize(float window_width, float window_height);

	void render();

	void updateWindowDimensions(float window_width, float window_height);

	FreeCamera _freeCamera;

private:
	Shader _shader;
	ShaderProgram _shaderProgram;
	TextureMaterial _texMaterial;
	std::unique_ptr<entity::IcoSphere> uvSphere;
};