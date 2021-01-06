#pragma once

#include <string>
#include <memory>
#include <vector>
#include "entity.h"
#include "../shadermanager.h"
#include "../freecamera.h"
#include "../lights/light.h"
#include "../collisions/collidable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class EntityContainer
{
public:
	EntityContainer(std::shared_ptr<FreeCamera> freeCamera);

	void addEntity(std::shared_ptr<entity::Entity> entity);

	bool deleteEntity(std::shared_ptr<entity::Entity> entity);

	void addLight(std::shared_ptr<light::Light> light);

	void setSelectedEntity(std::shared_ptr<entity::Entity> entity);

	void setSelectedEntityTexture(std::shared_ptr<TextureMaterial> entityTex);

	void drawEntities();

	std::shared_ptr<entity::Entity> selectedEntity();

	std::vector<std::shared_ptr<collisions::Collidable>> collidableEntities();

	void changeEntityShader(std::shared_ptr<entity::Entity> entity, const std::string& oldShaderName, const std::string& newShaderName);

private:
	void setLightUniforms(std::shared_ptr<ShaderProgram> shaderProgram);

private:
	ShaderManager* _shaderManager = nullptr;
	std::shared_ptr<FreeCamera> _freeCamera;
	// so we can draw all the related enities for a shader, might change later
	std::map<std::string, std::vector<std::shared_ptr<entity::Entity>>> _shaderEntityMap;
	// maintain list of all collidable entities for easy access
	std::vector<std::shared_ptr<collisions::Collidable>> _collidableEntities;
	std::vector<std::shared_ptr<light::Light>> _lights;
	std::shared_ptr<entity::Entity> _selectedEntity = nullptr;
	std::shared_ptr<TextureMaterial> _selectedEntityTexture = nullptr;
	std::shared_ptr<TextureMaterial> _selectedEntityOldTexture = nullptr;
};