#include "entityfactory.h"

#include "cube.h"

EntityFactory* EntityFactory::_instance = nullptr;
unsigned int EntityFactory::ENTITY_COUNT = 0;
std::shared_ptr<EntityContainer> EntityFactory::_entityContainer = nullptr;

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

std::shared_ptr<entity::Entity> EntityFactory::addEntity(const EntityFactory::EntityType entityType) {
	std::shared_ptr<entity::Entity> entity = nullptr;

	switch (entityType) {
		case EntityFactory::EntityType::Cube:
		{
			entity = std::make_shared<entity::Cube>("phongShader");
		}
	}

	if (entity != nullptr) {
		_entityContainer->addEntity("entity" + std::to_string(ENTITY_COUNT), entity);
	}

	return entity;
}