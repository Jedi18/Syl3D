#include "entitycontainer.h"

EntityContainer::EntityContainer(std::shared_ptr<ShaderManager> shaderManager)
	:
	_shaderManager(shaderManager)
{}

void EntityContainer::addEntity(std::string entityName, std::shared_ptr<entity::Entity> entity) {
	std::string shaderName = entity->shaderName();

	if (_shaderEntityMap.find(shaderName) == _shaderEntityMap.end()) {
		_shaderEntityMap[shaderName] = std::vector<std::shared_ptr<entity::Entity>>();
	}

	_shaderEntityMap[shaderName].push_back(entity);
}

void EntityContainer::drawEntities(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	for (auto iter = _shaderEntityMap.begin(); iter != _shaderEntityMap.end(); ++iter) {
		_shaderManager->useShader(iter->first);
		std::shared_ptr<ShaderProgram> shaderProgram = _shaderManager->currentShader();

		if (iter->first == "colorShader") {
			shaderProgram->setColor("objectColor", shading::Color(1.0f, 0.5f, 0.31f));
			shaderProgram->setColor("lightColor", shading::Color(1.0f, 1.0f, 1.0f));
		}

		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);

		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			shaderProgram->setMat4("model", ptr->modelMatrix());
			ptr->draw();
		}
	}
}