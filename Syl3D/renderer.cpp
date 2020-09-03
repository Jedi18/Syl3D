#include "renderer.h"
#include "mesh/rectanglemesh.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>

Renderer::Renderer() 
	:
	_shaderProgram(-1),
	_texMaterial(&_shaderProgram)
{}

void Renderer::initialize(float window_width, float window_height) {
	glEnable(GL_DEPTH_TEST);

	_shaderProgram = _shader.createShaderProgram("shaders/vertex1.shader", "shaders/fragment1.shader");

	uvSphere = std::make_unique<entity::UVSphere>();

	_texMaterial.addTexture("container.jpg");
	_texMaterial.addTexture("awesomeface.png", true, true);
	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.use();
	_texMaterial.activateTextures();

	_shaderProgram.setMat4("view", _freeCamera.viewMatrix());
	_shaderProgram.setMat4("projection", _freeCamera.projectionMatrix());

	_shaderProgram.setMat4("model", uvSphere->modelMatrix());
	uvSphere->draw();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera.updateWindowDimensions(window_width, window_height);
}