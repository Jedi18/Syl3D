#include "entitycontainer.h"

#include "entitymanager.h"
#include "../inputmanager.h"

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
	if (_selectedObject != nullptr && (entity->id() == _selectedObject->id())) {
		setSelectedObject(nullptr);
	}

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

void EntityContainer::setSelectedObject(std::shared_ptr<Object> object) {
	_selectedObject = object;
}

void EntityContainer::setSelectedObject(unsigned int entityId) {
	std::shared_ptr<entity::Entity> entity = entityById(entityId);
	if (entity != nullptr) {
		setSelectedObject(entity);
	}
	else {
		// light
		std::shared_ptr<light::Light> light = lightById(entityId);

		if (light != nullptr) {
			setSelectedObject(light);
		}
		else {
			setSelectedObject(nullptr);
		}
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

std::shared_ptr<light::Light> EntityContainer::lightById(unsigned int lightId) {
	for (std::shared_ptr<light::Light> light : _lights) {
		if (light->id() == lightId) {
			return light;
		}
	}

	return nullptr;
}

std::shared_ptr<Object> EntityContainer::selectedObject() {
	return _selectedObject;
}

void EntityContainer::setSkybox(std::shared_ptr<Skybox> skybox) {
	// ShaderManager is intialized in addEntity, so if setSkybox called before then initalize here
	if (_shaderManager == nullptr) {
		_shaderManager = ShaderManager::shaderManager();
	}

	_skybox = skybox;
}

void EntityContainer::drawEntities() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewMatrix = _freeCamera->viewMatrix();
	glm::mat4 projectionMatrix = _freeCamera->projectionMatrix();
	drawSkybox(viewMatrix, projectionMatrix);

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		_shaderManager->useShader(iter->first);
		std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();

		shaderProgram->setFloat("material.shininess", 32.0f);
		shaderProgram->setVec3("viewPos", _freeCamera->cameraPosition());

		setLightUniforms(shaderProgram);

		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);

		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			if (InputManager::guiMode && _selectedObject != nullptr && _selectedObject->id() == ptr->id()) {
				continue;
			}

			ptr->activateTexture();
			glm::mat4 modelMatrix = ptr->modelMatrix();
			shaderProgram->setMat4("model", modelMatrix);
			shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
			ptr->draw();
		}
	}

	if (_selectedObject != nullptr && InputManager::guiMode) {
		drawSelectedEntity(viewMatrix, projectionMatrix);
	}
}

void EntityContainer::drawSelectedEntity(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) {
	glClear(GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	std::shared_ptr<entity::Entity> _selectedEntity = std::dynamic_pointer_cast<entity::Entity>(_selectedObject);
	if (_selectedEntity != nullptr) {
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		// draw selected entity
		_selectedEntity->activateTexture();
		std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();
		glm::mat4 modelMatrix = _selectedEntity->modelMatrix();
		shaderProgram->setMat4("model", modelMatrix);
		shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);
		_selectedEntity->draw();

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		_shaderManager->useShader("singlecolorShader");
		math::Vec3 oldScale = _selectedEntity->getScale();
		_selectedEntity->scale(_selectedHighlightScaleFactor);

		// draw the enlarged selected entity in a single color
		shaderProgram = _shaderManager->currentShader();
		modelMatrix = _selectedEntity->modelMatrix();
		shaderProgram->setColor("color", _selectedHighlightColor);
		shaderProgram->setMat4("model", modelMatrix);
		shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);
		_selectedEntity->draw();

		_selectedEntity->setScale(oldScale);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

	glDisable(GL_STENCIL_TEST);
}

void EntityContainer::drawSkybox(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) {
	if (_skybox == nullptr) {
		return;
	}
	
	glDepthFunc(GL_LEQUAL);

	_shaderManager->useShader(_skybox->cubemap()->shaderName());
	std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();

	glm::mat4 viewSkybox = glm::mat3(viewMatrix);
	shaderProgram->setMat4("view", viewSkybox);
	shaderProgram->setMat4("projection", projectionMatrix);
	_skybox->activateCubemap();
	_skybox->draw();

	glDepthFunc(GL_LESS);
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

std::vector<std::shared_ptr<Object>> EntityContainer::objectList() {
	std::vector<std::shared_ptr<Object>> objectsList;

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			objectsList.push_back(ptr);
		}
	}

	for (std::shared_ptr<light::Light> light : _lights) {
		objectsList.push_back(light);
	}

	return objectsList;
}