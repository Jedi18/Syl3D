#include "renderer.h"
#include "mesh/rectanglemesh.h"

#include "utility/heightmapgenerator.h"
#include "texture/texturefactory.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "vendor/stb_image/stb_image.h"

#include "color.h"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

	TextureFactory* textureFactory = TextureFactory::textureFactory();
	textureFactory->setShaderManager(_shaderManager);

	_shaderManager->addShader("phongShader", "shaders/phongvertex.shader", "shaders/phongfragment.shader");
	_shaderManager->addShader("terrainShader", "shaders/phongvertex.shader", "shaders/terrainfragment.shader");

	textureFactory->addShader("phongShader");
	textureFactory->addShader("terrainShader");

	//std::shared_ptr<TextureMaterial> _texMaterial = std::make_shared<TextureMaterial>(_shaderManager->shaderByName("phongShader"));
	//_texMaterial->addTexture("material.diffuse", "resources/container2.png");
	//_texMaterial->addTexture("material.specular", "resources/container2_specular.png");
	std::shared_ptr<TextureMaterial> _texMaterial = textureFactory->addTextureMaterial("texMaterial", "resources/container2.png", "resources/container2_specular.png");
	_wallMaterial = textureFactory->addTextureMaterial("wallMaterial", "resources/wall.jpg", "resources/container2_specular.png");
	/*_wallMaterial = std::make_shared<TextureMaterial>(_shaderManager->shaderByName("phongShader"));
	_wallMaterial->addTexture("material.diffuse", "resources/wall.jpg");
	_wallMaterial->addTexture("material.specular", "resources/container2_specular.png");*/

	/*std::shared_ptr<TextureMaterial> _terrainTex = std::make_shared<TextureMaterial>(_shaderManager->shaderByName("terrainShader"));
	_terrainTex->addTexture("material.diffuse", "resources/snowtex.png");
	_terrainTex->addTexture("material.specular", "resources/container2_specular.png");*/

	std::shared_ptr<TextureMaterial> _terrainTex = textureFactory->addTextureMaterial("terrainTex", "resources/snowtex.png", "resources/container2_specular.png", "terrainShader");
	
	/*std::shared_ptr<TextureMaterial> _uvMat = std::make_shared<TextureMaterial>(_shaderManager->shaderByName("phongShader"));
	_uvMat->addTexture("material.diffuse", "resources/sphcol.jpg", false);
	_uvMat->addTexture("material.specular", "resources/sphspec.jpg", true);*/

	for (int i = 0; i < 10; i++) {
		float angle = 20.0f * i;
		std::shared_ptr<entity::Cube> cube = std::make_shared<entity::Cube>("phongShader");
		cube->translateTo(cubePositions[i]);
		cube->rotateAround(glm::radians(angle), math::Vec3(1.0f, 0.3f, 0.5f));
		cube->setTexture(_texMaterial);
		_entityContainer.addEntity("cube" + std::to_string(i), cube);

		_cubes.push_back(cube);
	}

	//utility::HeightmapData heightmapData = utility::HeightmapGenerator::ProceduralHeightmap(10, 10, 0.8f);
	utility::HeightmapData heightmapData = utility::HeightmapGenerator::LoadHeightmapFromFile("resources/snow1.png");
	
	std::shared_ptr<entity::Terrain> terrain1 = std::make_shared<entity::Terrain>(heightmapData, "terrainShader");
	terrain1->setTexture(_terrainTex);
	terrain1->translateTo(math::Vec3(0.0f, -5.0f, 0.0f));
	terrain1->scale(20);
	_entityContainer.addEntity("terrain1", terrain1);

	std::shared_ptr<entity::Model> model1 = utility::ModelFactory::loadModel("resources/backpack/backpack.obj", "phongShader", _shaderManager->shaderByName("phongShader"));
	model1->translate(math::Vec3(0, -4, 0));
	_entityContainer.addEntity("model1", model1);

	_spotLight = std::make_shared<light::SpotLight>(_freeCamera->cameraPosition(), _freeCamera->cameraFrontDirection(), shading::Color(0.8f, 0.8f, 0.8f));

	_entityContainer.addLight(std::make_shared<light::PointLight>(math::Vec3(0.7f, 0.2f, 2.0f), shading::Color(0.8f, 0.8f, 0.8f)));
	_entityContainer.addLight(std::make_shared<light::DirectionalLight>(math::Vec3(-0.2f, -1.0f, -0.3f), shading::Color(0.7f, 0.7f, 0.7f)));
	_entityContainer.addLight(_spotLight);

	updateWindowDimensions(window_width, window_height);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_spotLight->setPosition(_freeCamera->cameraPosition());
	_spotLight->setDirection(_freeCamera->cameraFrontDirection());
	_entityContainer.drawEntities();
}

void Renderer::updateWindowDimensions(float window_width, float window_height) {
	_freeCamera->updateWindowDimensions(window_width, window_height);
}

void Renderer::mouseRayIntersections(math::Vec3 mouseRay) {
	math::Ray ray(_freeCamera->cameraPosition(), mouseRay);
	for (std::shared_ptr<entity::Cube> cube : _cubes) {
		if (cube->intersects(ray)) {
			cube->setTexture(_wallMaterial);
		}
	}
}

EntityFactory& Renderer::entityFactory() {
	return _entityFactory;
}