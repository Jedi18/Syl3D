#include "entityfactory.h"

#include "cube.h"
#include "uvsphere.h"
#include "icosphere.h"
#include "terrain.h"
#include "../texture/texturefactory.h"

EntityFactory* EntityFactory::_instance = nullptr;
unsigned int EntityFactory::ENTITY_COUNT = 0;

std::map<EntityFactory::EntityType, std::string> EntityFactory::ENTITY_NAMES = {
	{EntityFactory::EntityType::Cube, "Cube"},
	{EntityFactory::EntityType::UVSphere, "UVSphere"},
	{EntityFactory::EntityType::IcoSphere, "IcoSphere"}
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

unsigned int EntityFactory::generateID() {
	ENTITY_COUNT++;
	return ENTITY_COUNT;
}