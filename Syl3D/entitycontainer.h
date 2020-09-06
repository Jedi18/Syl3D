#pragma once

#include <string>
#include <memory>
#include <vector>
#include "entity/entity.h"
#include "shadermanager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class EntityContainer
{
public:
	EntityContainer(std::shared_ptr<ShaderManager> shaderManager);

	void addEntity(std::string entityName, std::shared_ptr<entity::Entity> entity);

	void drawEntities(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	std::shared_ptr<ShaderManager> _shaderManager;
	// so we can draw all the related enities for a shader, might change later
	std::map<std::string, std::vector<std::shared_ptr<entity::Entity>>> _shaderEntityMap;
};