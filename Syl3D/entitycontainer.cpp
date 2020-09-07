#include "entitycontainer.h"

EntityContainer::EntityContainer(std::shared_ptr<ShaderManager> shaderManager, std::shared_ptr<FreeCamera> freeCamera)
	:
	_shaderManager(shaderManager),
	_freeCamera(freeCamera)
{}

void EntityContainer::addEntity(std::string entityName, std::shared_ptr<entity::Entity> entity) {
	std::string shaderName = entity->shaderName();

	if (_shaderEntityMap.find(shaderName) == _shaderEntityMap.end()) {
		_shaderEntityMap[shaderName] = std::vector<std::shared_ptr<entity::Entity>>();
	}

	_shaderEntityMap[shaderName].push_back(entity);
}

void EntityContainer::drawEntities() {
	glm::mat4 viewMatrix = _freeCamera->viewMatrix();
	glm::mat4 projectionMatrix = _freeCamera->projectionMatrix();

	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		_shaderManager->useShader(iter->first);
		std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();

		if (iter->first == "phongShader") {
			shaderProgram->setColor3("objectColor", shading::Color(1.0f, 0.5f, 0.31f));
			shaderProgram->setColor3("lightColor", shading::Color(1.0f, 1.0f, 1.0f));
			shaderProgram->setVec3("lightPos", lightPos);
			shaderProgram->setVec3("viewPos", _freeCamera->cameraPosition());
		}

		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);

		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			glm::mat4 modelMatrix = ptr->modelMatrix();
			shaderProgram->setMat4("model", modelMatrix);
			shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
			ptr->draw();
		}
	}
}