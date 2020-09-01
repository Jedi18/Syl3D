#include "renderer.h"
#include "mesh/rectanglemesh.h"
#include "mesh/coloredtriangle.h"
#include "mesh/texturedrectangle.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Renderer::Renderer() 
	:
	_shaderProgram(-1),
	_texMaterial(&_shaderProgram)
{}

void Renderer::initialize() {
	glEnable(GL_DEPTH_TEST);
	_shaderProgram = _shader.createShaderProgram("shaders/vertex1.shader", "shaders/fragment1.shader");

	_rectangle = new entity::Rectangle();
	_triangle = new entity::Triangle();
	_cube = new entity::Cube();

	_texMaterial.addTexture("container.jpg");
	_texMaterial.addTexture("awesomeface.png", true, true);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	_shaderProgram.use();
	_texMaterial.activateTextures();
	_shaderProgram.setFloat("visibility", vis);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	_shaderProgram.setMat4("view", view);
	_shaderProgram.setMat4("projection", projection);

	for (unsigned int i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		_shaderProgram.setMat4("model", model);
		_cube->draw();
	}
	//_rectangle->draw();
	//_triangle->draw();
}