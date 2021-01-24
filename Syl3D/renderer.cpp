#include "renderer.h"
#include "mesh/rectanglemesh.h"

#include "utility/heightmapgenerator.h"
#include "texture/texturefactory.h"
#include "collisions/collidable.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "vendor/stb_image/stb_image.h"

#include "color.h"
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Renderer::Renderer() 
	:
	_freeCamera(std::make_shared<FreeCamera>()),
	_mousePicker(_freeCamera),
	_entityContainer(std::make_shared<EntityContainer>(_freeCamera))
{}

void Renderer::initialize(float window_width, float window_height) {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	ShaderManager* shaderManager = ShaderManager::shaderManager();
	TextureFactory* textureFactory = TextureFactory::textureFactory();

	shaderManager->addShader("phongShader", "shaders/phongvertex.shader", "shaders/phongfragment.shader");
	shaderManager->addShader("terrainShader", "shaders/phongvertex.shader", "shaders/terrainfragment.shader");
	shaderManager->addShader("skyboxShader", "shaders/skyboxvertex.shader", "shaders/skyboxfragment.shader");

	textureFactory->addShader("phongShader");
	textureFactory->addShader("terrainShader");
	textureFactory->addShader("skyboxShader");

	textureFactory->addTexturesFromFolder("resources/textures");

	//std::shared_ptr<TextureMaterial> _texMaterial = textureFactory->addTextureMaterial("texMaterial", "resources/container2.png", "resources/container2_specular.png");
	//std::shared_ptr<TextureMaterial> _wallMaterial = textureFactory->addTextureMaterial("wallMaterial", "resources/wall.jpg", "resources/container2_specular.png");
	//std::shared_ptr<TextureMaterial> _terrainTex = textureFactory->addTextureMaterial("terrainTex", "resources/snowtex.png", "resources/container2_specular.png", "terrainShader");

	EntityFactory* entityFactory = EntityFactory::entityFactory();
	entityFactory->setEntityContainer(_entityContainer);

	/*std::shared_ptr<entity::Model> model1 = utility::ModelFactory::loadModel("resources/backpack/backpack.obj", "phongShader", _shaderManager->shaderByName("phongShader"));
	model1->translate(math::Vec3(0, -4, 0));
	_entityContainer->addEntity("model1", model1);*/

	_spotLight = std::make_shared<light::SpotLight>(_freeCamera->cameraPosition(), _freeCamera->cameraFrontDirection(), shading::Color(0.8f, 0.8f, 0.8f));
	_entityContainer->addLight(_spotLight);

	std::shared_ptr<CubeMap> skycubebox1 = std::make_shared<CubeMap>("resources/skyboxes/skybox1");
	std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>();
	skybox->setCubemap(skycubebox1);
	_entityContainer->setSkybox(skybox);
	
	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_spotLight->translateTo(_freeCamera->cameraPosition());
	_spotLight->setDirection(_freeCamera->cameraFrontDirection());
	_entityContainer->drawEntities();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera->updateWindowDimensions(window_width, window_height);
}

void Renderer::mouseRayIntersections(math::Vec3 mouseRay) {
	math::Ray ray(_freeCamera->cameraPosition(), mouseRay);
	std::vector<std::shared_ptr<collisions::Collidable>> collidableEntities = _entityContainer->collidableEntities();
	for (std::shared_ptr<collisions::Collidable> collidable : collidableEntities) {
		if (collidable->intersects(ray)) {
			_entityContainer->setSelectedObject(std::dynamic_pointer_cast<entity::Entity>(collidable));
		}
	}
}