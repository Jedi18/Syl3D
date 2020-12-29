#include "entityfactory.h"

#include "cube.h"
#include "uvsphere.h"
#include "icosphere.h"
#include "terrain.h"
#include "../texture/texturefactory.h"

EntityFactory* EntityFactory::_instance = nullptr;
unsigned int EntityFactory::ENTITY_COUNT = 0;
std::map<int, std::string> EntityFactory::_defaultShaders = std::map<int, std::string>();

std::map<EntityFactory::EntityType, std::string> EntityFactory::ENTITY_NAMES = {
	{EntityFactory::EntityType::Cube, "Cube"},
	{EntityFactory::EntityType::UVSphere, "UVSphere"},
	{EntityFactory::EntityType::IcoSphere, "IcoSphere"}
};

EntityFactory::EntityFactory() {
	for (int entityT = (int)EntityType::Cube; entityT <= (int)EntityType::IcoSphere; entityT++) {
		_defaultShaders[entityT] = "phongShader";
	}
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
			entity = std::make_shared<entity::Cube>(_defaultShaders[(int)EntityFactory::EntityType::Cube]);
			break;
		}
		case EntityFactory::EntityType::UVSphere:
		{
			entity = std::make_shared<entity::UVSphere>(10,10,_defaultShaders[(int)EntityFactory::EntityType::UVSphere]);
			break;
		}
		case EntityFactory::EntityType::IcoSphere:
		{
			entity = std::make_shared<entity::IcoSphere>(3, _defaultShaders[(int)EntityFactory::EntityType::IcoSphere]);
			break;
		}
	}

	if (entity != nullptr) {
		_entityContainer->addEntity(entity);
		entity->setTexture(textureFactory->getTextureMaterial("texMaterial"));
	}

	return entity;
}

unsigned int EntityFactory::generateID() {
	ENTITY_COUNT++;
	return ENTITY_COUNT;
}