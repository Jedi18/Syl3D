#include "entitycontainer.h"

#include "entitymanager.h"

EntityContainer::EntityContainer(std::shared_ptr<FreeCamera> freeCamera)
	:
	_freeCamera(freeCamera)
{}

void EntityContainer::addEntity(std::shared_ptr<entity::Entity> entity) {
	// shader manager can't be instantiated on entitycontainer constructor as it's not ready to load the default texture at that point
	// instantiating it here works since shaderManager won't be used in drawEntity until addEntity is called at least once
	if (_shaderManager == nullptr) {
		_shaderManager = ShaderManager::shaderManager();
	}

	std::string shaderName = entity->texture()->shaderName();

	if (_shaderEntityMap.find(shaderName) == _shaderEntityMap.end()) {
		_shaderEntityMap[shaderName] = std::vector<std::shared_ptr<entity::Entity>>();
	}

	_shaderEntityMap[shaderName].push_back(entity);

	if (std::dynamic_pointer_cast<collisions::Collidable>(entity) != nullptr) {
		_collidableEntities.push_back(std::dynamic_pointer_cast<collisions::Collidable>(entity));
	}
}

bool EntityContainer::deleteEntity(std::shared_ptr<entity::Entity> entity) {
	std::string shaderName = entity->texture()->shaderName();

	if (_shaderEntityMap.find(shaderName) == _shaderEntityMap.end()) {
		return false;
	}

	_shaderEntityMap[shaderName].erase(std::remove(_shaderEntityMap[shaderName].begin(), _shaderEntityMap[shaderName].end(), entity), _shaderEntityMap[shaderName].end());
	
	std::shared_ptr<collisions::Collidable> collid = std::dynamic_pointer_cast<collisions::Collidable>(entity);
	if (collid != nullptr) { 
		_collidableEntities.erase(std::remove(_collidableEntities.begin(), _collidableEntities.end(), collid), _collidableEntities.end());
	}

	return true;
}

void EntityContainer::addLight(std::shared_ptr<light::Light> light) {
	_lights.push_back(light);
}

void EntityContainer::setSelectedEntity(std::shared_ptr<entity::Entity> entity) {
	if (_selectedEntity != nullptr && _selectedEntityOldTexture != nullptr) {
		//entity::EntityManager::entityManager()->changeTexture(_selectedEntity, _selectedEntityOldTexture);
	}

	if (_selectedEntityTexture != nullptr) {
		_selectedEntityOldTexture = entity->texture();
		//entity::EntityManager::entityManager()->changeTexture(entity, _selectedEntityTexture);
	}

	_selectedEntity = entity;
}

void EntityContainer::setSelectedEntity(unsigned int entityId) {
	std::shared_ptr<entity::Entity> entity = entityById(entityId);
	if (entity != nullptr) {
		setSelectedEntity(entity);
	}
}

std::shared_ptr<entity::Entity> EntityContainer::entityById(unsigned int entityId) {
	std::vector<std::shared_ptr<entity::Entity>> entitiesList;

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			if (ptr->id() == entityId) {
				return ptr;
			}
		}
	}

	return nullptr;
}

std::shared_ptr<entity::Entity> EntityContainer::selectedEntity() {
	return _selectedEntity;
}

void EntityContainer::drawEntities() {
	glm::mat4 viewMatrix = _freeCamera->viewMatrix();
	glm::mat4 projectionMatrix = _freeCamera->projectionMatrix();

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		_shaderManager->useShader(iter->first);
		std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();

		shaderProgram->setFloat("material.shininess", 32.0f);
		shaderProgram->setVec3("viewPos", _freeCamera->cameraPosition());

		setLightUniforms(shaderProgram);

		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);

		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			ptr->activateTexture();
			glm::mat4 modelMatrix = ptr->modelMatrix();
			shaderProgram->setMat4("model", modelMatrix);
			shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
			ptr->draw();
		}
	}
}

void EntityContainer::setLightUniforms(std::shared_ptr<ShaderProgram> shaderProgram) {
	int numDirLights = 0;
	int numPointLights = 0;
	int numSpotLights = 0;

	for (std::shared_ptr<light::Light> light : _lights) {
		switch (light->type()) {
		case light::Light::LightType::Point:
			light->setShaderUniforms(shaderProgram, numPointLights);
			numPointLights++;
			break;
		case light::Light::LightType::Directional:
			light->setShaderUniforms(shaderProgram, numDirLights);
			numDirLights++;
			break;
		case light::Light::LightType::SpotLight:
			light->setShaderUniforms(shaderProgram, numSpotLights);
			numSpotLights++;
			break;
		}
	}

	shaderProgram->setInt("numDirLights", numDirLights);
	shaderProgram->setInt("numPointLights", numPointLights);
	shaderProgram->setInt("numSpotLights", numSpotLights);
}

std::vector<std::shared_ptr<collisions::Collidable>> EntityContainer::collidableEntities() {
	return _collidableEntities;
}

void EntityContainer::setSelectedEntityTexture(std::shared_ptr<TextureMaterial> entityTex) {
	_selectedEntityTexture = entityTex;
}

void EntityContainer::changeEntityShader(std::shared_ptr<entity::Entity> entity, const std::string& oldShaderName, const std::string& newShaderName) {
	for (auto iter = _shaderEntityMap[oldShaderName].begin(); iter != _shaderEntityMap[oldShaderName].end(); ++iter) {
		if ((*iter)->id() == entity->id()) {
			_shaderEntityMap[oldShaderName].erase(iter);
			break;
		}
	}

	_shaderEntityMap[newShaderName].push_back(entity);
}

std::vector<std::shared_ptr<entity::Entity>> EntityContainer::entityList() {
	std::vector<std::shared_ptr<entity::Entity>> entitiesList;

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			entitiesList.push_back(ptr);
		}
	}

	return entitiesList;
}