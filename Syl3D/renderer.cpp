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

	math::Vec3 cubePositions[] = {
	math::Vec3(0.0f,  0.0f,  0.0f),
	math::Vec3(2.0f,  5.0f, -15.0f),
	math::Vec3(-1.5f, -2.2f, -2.5f),
	math::Vec3(-3.8f, -2.0f, -12.3f),
	math::Vec3(2.4f, -0.4f, -3.5f),
	math::Vec3(-1.7f,  3.0f, -7.5f),
	math::Vec3(1.3f, -2.0f, -2.5f),
	math::Vec3(1.5f,  2.0f, -2.5f),
	math::Vec3(1.5f,  0.2f, -1.5f),
	math::Vec3(-1.3f,  1.0f, -1.5f)
	};

	_shaderManager->addShader("phongShader", "shaders/directionalvertex.shader", "shaders/spotlightfragment.shader");
	//_shaderManager->addShader("lampShader", "shaders/matvertex.shader", "shaders/lampfragment.shader");

	std::shared_ptr<TextureMaterial> _texMaterial = std::make_shared<TextureMaterial>(_shaderManager->shaderByName("phongShader"));
	_texMaterial->addTexture("material.diffuse", "container2.png", true);
	_texMaterial->addTexture("material.specular", "container2_specular.png", true);

	//lamp = std::make_shared<entity::UVSphere>(10, 10, "lampShader");
	
	for (int i = 0; i < 10; i++) {
		float angle = 20.0f * i;
		std::shared_ptr<entity::Cube> cube = std::make_shared<entity::Cube>("phongShader");
		cube->translateTo(cubePositions[i]);
		cube->rotateAround(glm::radians(angle), math::Vec3(1.0f, 0.3f, 0.5f));
		cube->setTexture(_texMaterial);
		_entityContainer.addEntity("cube" + std::to_string(i), cube);
	}

	//lamp->translate(math::Vec3(-0.2f, 0.0f, -0.0f));
	//_entityContainer.addEntity("lamp", lamp);

	//_entityContainer.lightPos = lamp->position();

	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//_entityContainer.lightPos = math::Vec3(1.0f + sin(glfwGetTime()) * 10.0f, 0, sin(glfwGetTime() / 2.0f) * 10.0f);
	//lamp->translateTo(math::Vec3(1.0f + sin(glfwGetTime()) * 10.0f, 0, sin(glfwGetTime() / 2.0f) * 10.0f));

	_entityContainer.drawEntities();

	//_shaderProgram.setMat4("model", terrain->modelMatrix());
	//terrain->draw();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera->updateWindowDimensions(window_width, window_height);
}