#pragma once

#include "shader.h"
#include "texturematerial.h"
#include "entity/rectangle.h"
#include "entity/triangle.h"
#include "entity/cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
public:
	Renderer();

	void initialize();

	void render();

	// temp
	float vis;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float pitch = 0.0f;
	float yaw = -90.0f;
	float roll = 0.0f;
	float _zoom = 45.0f;

private:
	Shader _shader;
	ShaderProgram _shaderProgram;
	TextureMaterial _texMaterial;
	entity::Rectangle* _rectangle;
	entity::Triangle* _triangle;
	entity::Cube* _cube;
};