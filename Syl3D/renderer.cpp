#include "renderer.h"
#include "mesh/rectanglemesh.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "color.h"
#include <iostream>

Renderer::Renderer() 
	:
	_freeCamera(std::make_shared<FreeCamera>()),
	_mousePicker(_freeCamera),
	_shaderManager(std::make_shared<ShaderManager>()),
	_entityContainer(_shaderManager, _freeCamera)
{}

void Renderer::initialize(float window_width, float window_height) {
	_shaderManager->initialize();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	_shaderManager->addShader("phongShader", "shaders/phongvertex.shader", "shaders/phongfragment.shader");
	_shaderManager->addShader("lampShader", "shaders/phongvertex.shader", "shaders/lampfragment.shader");

	lamp = std::make_shared<entity::UVSphere>(10, 10, "lampShader");
	std::shared_ptr<entity::Cube> cube1 = std::make_shared<entity::Cube>("phongShader");

	lamp->translate(math::Vec3(-5.2f, 5.0f, -5.0f));

	_entityContainer.addEntity("cube1", cube1);
	_entityContainer.addEntity("lamp", lamp);

	_entityContainer.lightPos = lamp->position();

	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_entityContainer.lightPos = math::Vec3(1.0f + sin(glfwGetTime()) * 10.0f, 0, sin(glfwGetTime() / 2.0f) * 10.0f);
	lamp->translateTo(math::Vec3(1.0f + sin(glfwGetTime()) * 10.0f, 0, sin(glfwGetTime() / 2.0f) * 10.0f));

	_entityContainer.drawEntities();

	//_shaderProgram.setMat4("model", terrain->modelMatrix());
	//terrain->draw();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera->updateWindowDimensions(window_width, window_height);
}