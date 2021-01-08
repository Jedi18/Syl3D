#include "entityfactory.h"

#include "cube.h"
#include "uvsphere.h"
#include "icosphere.h"
#include "../lights/pointlight.h"
#include "../lights/directionallight.h"
#include "../lights/spotlight.h"

#include "terrain.h"
#include "../texture/texturefactory.h"

EntityFactory* EntityFactory::_instance = nullptr;
unsigned int EntityFactory::ENTITY_COUNT = 0;

std::map<EntityFactory::EntityType, std::string> EntityFactory::ENTITY_NAMES = {
	{EntityFactory::EntityType::Cube, "Cube"},
	{EntityFactory::EntityType::UVSphere, "UVSphere"},
	{EntityFactory::EntityType::IcoSphere, "IcoSphere"}
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
	}

	if (entity != nullptr) {
		// material needs to be applied before adding to entity container (maybe instead 
		// should check for null and add default in entity container?)
		entity->setTexture(textureFactory->getTextureMaterial("texMaterial"));
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

unsigned int EntityFactory::generateID() {
	ENTITY_COUNT++;
	return ENTITY_COUNT;
}