#include "renderer.h"
#include "mesh/rectanglemesh.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "color.h"
#include <iostream>

Renderer::Renderer() 
	:
	_mousePicker(&_freeCamera),
	_shaderManager(std::make_shared<ShaderManager>()),
	_entityContainer(_shaderManager)
{}

void Renderer::initialize(float window_width, float window_height) {
	_shaderManager->initialize();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	_shaderManager->addShader("colorShader", "shaders/colorvertex.shader", "shaders/colorfragment.shader");
	_shaderManager->addShader("lampShader", "shaders/colorvertex.shader", "shaders/lampfragment.shader");

	std::shared_ptr<entity::UVSphere> lamp = std::make_shared<entity::UVSphere>(10, 10, "lampShader");
	std::shared_ptr<entity::Cube> cube1 = std::make_shared<entity::Cube>("colorShader");
	//terrain = std::make_unique<entity::Terrain>();
	//terrain->scale(10);

	lamp->translate(math::Vec3(5.2f, 5.0f, 5.0f));

	_entityContainer.addEntity("cube1", cube1);
	_entityContainer.addEntity("lamp", lamp);

	//_texMaterial.addTexture("container.jpg");
	//_texMaterial.addTexture("awesomeface.png", true, true);
	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_entityContainer.drawEntities(_freeCamera.viewMatrix(), _freeCamera.projectionMatrix());

	//_shaderProgram.setMat4("model", terrain->modelMatrix());
	//terrain->draw();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera.updateWindowDimensions(window_width, window_height);
}