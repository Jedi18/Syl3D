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
			shaderProgram->setFloat("material.shininess", 32.0f);

			shaderProgram->setColor3("light.ambient", shading::Color(0.2f, 0.2f, 0.2f));
			shaderProgram->setColor3("light.diffuse", shading::Color(0.5f, 0.5f, 0.5f));
			shaderProgram->setColor3("light.specular", shading::Color(1.0f, 1.0f, 1.0f));

			shaderProgram->setVec3("light.position", _freeCamera->cameraPosition());
			shaderProgram->setVec3("light.direction", _freeCamera->cameraFrontDirection());
			shaderProgram->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
			shaderProgram->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5)));

			/* Spotlight
			shaderProgram->setVec3("light.position", lightPos);
			shaderProgram->setFloat("light.constant", 1.0f);
			shaderProgram->setFloat("light.linearConstant", 0.09f);
			shaderProgram->setFloat("light.quadraticConstant", 0.032f); */

			/* Directional
			shaderProgram->setVec3("light.direction", math::Vec3(-0.2f, -1.0f, -0.3f));*/

			shaderProgram->setVec3("viewPos", _freeCamera->cameraPosition());
		}

		shaderProgram->setMat4("view", viewMatrix);
		shaderProgram->setMat4("projection", projectionMatrix);

		for (std::shared_ptr<entity::Entity> ptr : iter->second) {
			if (iter->first == "phongShader") {
				ptr->activateTexture();
			}
			glm::mat4 modelMatrix = ptr->modelMatrix();
			shaderProgram->setMat4("model", modelMatrix);
			shaderProgram->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));
			ptr->draw();
		}
	}
}