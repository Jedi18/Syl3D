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

			/* Directional Light */
			shaderProgram->setColor3("dirLights[0].ambient", shading::Color(0.1f, 0.1f, 0.1f));
			shaderProgram->setColor3("dirLights[0].diffuse", shading::Color(0.4f, 0.4f, 0.4f));
			shaderProgram->setColor3("dirLights[0].specular", shading::Color(0.5f, 0.5f, 0.5f));
			shaderProgram->setVec3("dirLights[0].direction", math::Vec3(-0.2f, -1.0f, -0.3f));

			/* Point Light */
			shaderProgram->setVec3("pointLights[0].position", math::Vec3(0.7f, 0.2f, 2.0f));
			shaderProgram->setColor3("pointLights[0].ambient", shading::Color(0.05f, 0.05f, 0.05f));
			shaderProgram->setColor3("pointLights[0].diffuse", shading::Color(0.8f, 0.8f, 0.8f));
			shaderProgram->setColor3("pointLights[0].specular", shading::Color(1.0f, 1.0f, 1.0f));
			shaderProgram->setFloat("pointLights[0].constant", 1.0f);
			shaderProgram->setFloat("pointLights[0].linearConstant", 0.09f);
			shaderProgram->setFloat("pointLights[0].quadraticConstant", 0.032f);

			/* Spot Light */
			shaderProgram->setColor3("spotLights[0].ambient", shading::Color(0.0f, 0.0f, 0.0f));
			shaderProgram->setColor3("spotLights[0].diffuse", shading::Color(0.8f, 0.8f, 0.8f));
			shaderProgram->setColor3("spotLights[0].specular", shading::Color(1.0f, 1.0f, 1.0f));
			shaderProgram->setFloat("spotLight[0].constant", 1.0f);
			shaderProgram->setFloat("spotLight[0].linear", 0.09);
			shaderProgram->setFloat("spotLight[0].quadratic", 0.032);

			shaderProgram->setVec3("spotLights[0].position", _freeCamera->cameraPosition());
			shaderProgram->setVec3("spotLights[0].direction", _freeCamera->cameraFrontDirection());
			shaderProgram->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
			shaderProgram->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(17.5)));

			shaderProgram->setVec3("viewPos", _freeCamera->cameraPosition());

			shaderProgram->setInt("numDirLights", 1);
			shaderProgram->setInt("numPointLights", 1);
			shaderProgram->setInt("numSpotLights", 1);
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