#include "entityfactory.h"

#include "cube.h"
#include "uvsphere.h"
#include "icosphere.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include "../lights/pointlight.h"
#include "../lights/directionallight.h"
#include "../lights/spotlight.h"
#include "../utility/fileio.h"

#include "terrain.h"
#include "../texture/texturefactory.h"

EntityFactory* EntityFactory::_instance = nullptr;
unsigned int EntityFactory::ENTITY_COUNT = 0;

std::map<EntityFactory::EntityType, std::string> EntityFactory::ENTITY_NAMES = {
	{EntityFactory::EntityType::Cube, "Cube"},
	{EntityFactory::EntityType::UVSphere, "UVSphere"},
	{EntityFactory::EntityType::IcoSphere, "IcoSphere"},
	{EntityFactory::EntityType::Triangle, "Triangle"},
	{EntityFactory::EntityType::Circle, "Circle"},
	{EntityFactory::EntityType::Rectangle, "Rectangle"}
};

std::map<EntityFactory::LightType, std::string> EntityFactory::LIGHT_NAMES = {
	{EntityFactory::LightType::Point, "Point"},
	{EntityFactory::LightType::Directional, "Directional"},
	{EntityFactory::LightType::Spot, "Spot"}
};

EntityFactory::EntityFactory() {
}

EntityFactory* EntityFactory::entityFactory() {
	if (_instance == nullptr) {
		_instance = new EntityFactory();
	}

	return _instance;
}

void EntityFactory::releaseInstance() {
	if (_instance != nullptr) {
		delete _instance;
	}
}

void EntityFactory::setEntityContainer(std::shared_ptr<EntityContainer> entityContainer) {
	_entityContainer = entityContainer;
}

std::shared_ptr<EntityContainer> EntityFactory::entityContainer() {
	return _entityContainer;
}

std::shared_ptr<entity::Entity> EntityFactory::addEntity(const EntityFactory::EntityType entityType) {
	std::shared_ptr<entity::Entity> entity = nullptr;
	TextureFactory* textureFactory = TextureFactory::textureFactory();

	switch (entityType) {
		case EntityFactory::EntityType::Cube:
		{
			entity = std::make_shared<entity::Cube>();
			break;
		}
		case EntityFactory::EntityType::UVSphere:
		{
			entity = std::make_shared<entity::UVSphere>(10,10);
			break;
		}
		case EntityFactory::EntityType::IcoSphere:
		{
			entity = std::make_shared<entity::IcoSphere>(3);
			break;
		}
		case EntityFactory::EntityType::Triangle:
		{
			entity = std::make_shared<entity::Triangle>();
			break;
		}
		case EntityFactory::EntityType::Circle:
		{
			entity = std::make_shared<entity::Circle>();
			break;
		}
		case EntityFactory::EntityType::Rectangle:
		{
			entity = std::make_shared<entity::Rectangle>();
			break;
		}
	}

	if (entity != nullptr) {
		// material needs to be applied before adding to entity container (maybe instead 
		// should check for null and add default in entity container?)
		entity->setTexture(textureFactory->getTextureMaterial("default"));
		_entityContainer->addEntity(entity);
	}

	return entity;
}

std::shared_ptr<light::Light> EntityFactory::addLight(const EntityFactory::LightType lightType) {
	std::shared_ptr<light::Light> light = nullptr;

	switch (lightType) {
	case EntityFactory::LightType::Point:
	{
		light = std::make_shared<light::PointLight>(math::Vec3(0.0f, 0.0f, 0.0f), shading::Color(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
	case EntityFactory::LightType::Directional:
	{
		light = std::make_shared<light::DirectionalLight>(math::Vec3(-0.2f, -1.0f, -0.3f), shading::Color(0.8f, 0.8f, 0.8f, 1.0f));
		break;
	}
	case EntityFactory::LightType::Spot:
	{
		light = std::make_shared<light::SpotLight>(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3(0.0f, 0.0f, 1.0f), shading::Color(0.8f, 0.8f, 0.8f));
		break;
	}
	}

	if (light != nullptr) {
		_entityContainer->addLight(light);
	}

	return light;
}

std::shared_ptr<entity::Terrain> EntityFactory::loadTerrain(const std::string& terrainFolder) {
	std::string folderPath = "resources/terrains/" + terrainFolder;
	std::vector<std::string> terrainFiles = utility::FileIO::filesInPath(folderPath);

	std::string heightMapFile = "";
	std::string textureFile = "";
	std::string specularFile = "";
	std::string textureName = "";

	for (const std::string& terrainFile : terrainFiles) {
		if (terrainFile.find("heightmap") != std::string::npos) {
			heightMapFile = folderPath + "/" + terrainFile;
		}

		if (terrainFile.find("texture") != std::string::npos) {
			textureFile = folderPath + "/" + terrainFile;
			textureName = terrainFile;
		}

		if (terrainFile.find("specular") != std::string::npos) {
			specularFile = folderPath + "/" + terrainFile;
		}
	}

	utility::HeightmapData heightmapData = utility::HeightmapGenerator::LoadHeightmapFromFile(heightMapFile);

	std::shared_ptr<TextureMaterial> newTex = nullptr;
	if (specularFile == "") {
		newTex = TextureFactory::textureFactory()->addTextureMaterial(textureName, textureFile, "resources/textures/default_specular.jpg", "terrainShader");
	}
	else {
		newTex = TextureFactory::textureFactory()->addTextureMaterial(textureName, textureFile, specularFile, "terrainShader");
	}

	std::shared_ptr<entity::Terrain> terrain = std::make_shared<entity::Terrain>(heightmapData);
	terrain->setTexture(newTex);
	terrain->translateTo(math::Vec3(0.0f, -5.0f, 0.0f));
	terrain->scale(20);
	_entityContainer->addEntity(terrain);

	return terrain;
}

unsigned int EntityFactory::generateID() {
	ENTITY_COUNT++;
	return ENTITY_COUNT;
}