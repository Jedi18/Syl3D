#include "entitymanager.h"

#include "entityfactory.h"
#include "entitycontainer.h"

using namespace entity;

EntityManager* EntityManager::_instance = nullptr;

EntityManager::EntityManager() {

}

EntityManager* EntityManager::entityManager() {
	if (_instance == nullptr) {
		_instance = new EntityManager();
	}

	return _instance;
}

void EntityManager::releaseInstance() {
	if (_instance != nullptr) {
		delete _instance;
	}
}

void EntityManager::changeTexture(std::shared_ptr<entity::Entity> entity, std::shared_ptr<TextureMaterial> newTextureMaterial) const {
	if (entity->texture()->shaderName() != newTextureMaterial->shaderName()) {
		std::shared_ptr<EntityContainer> entityContainer = EntityFactory::entityFactory()->entityContainer();
		entityContainer->changeEntityShader(entity, entity->texture()->shaderName(), newTextureMaterial->shaderName());
	}

	entity->setTexture(newTextureMaterial);
}