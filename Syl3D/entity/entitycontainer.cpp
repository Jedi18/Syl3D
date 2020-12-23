#include "entitycontainer.h"

EntityContainer::EntityContainer(std::shared_ptr<ShaderManager> shaderManager, std::shared_ptr<FreeCamera> freeCamera)
	:
	_shaderManager(shaderManager),
	_freeCamera(freeCamera)
{}

void EntityContainer::addEntity(std::shared_ptr<entity::Entity> entity) {
	std::string shaderName = entity->shaderName();

	if (_shaderEntityMap.find(shaderName) == _shaderEntityMap.end()) {
		_shaderEntityMap[shaderName] = std::vector<std::shared_ptr<entity::Entity>>();
	}

	_shaderEntityMap[shaderName].push_back(entity);

	if (std::dynamic_pointer_cast<collisions::Collidable>(entity) != nullptr) {
		_collidableEntities.push_back(std::dynamic_pointer_cast<collisions::Collidable>(entity));
	}
}

void EntityContainer::addLight(std::shared_ptr<light::Light> light) {
	_lights.push_back(light);
}

void EntityContainer::setSelectedEntity(std::shared_ptr<entity::Entity> entity) {
	_selectedEntity = entity;
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