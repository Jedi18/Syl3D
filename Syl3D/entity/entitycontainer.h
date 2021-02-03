#pragma once

#include <string>
#include <memory>
#include <vector>
#include "entity.h"
#include "../shadermanager.h"
#include "../freecamera.h"
#include "../lights/light.h"
#include "../collisions/collidable.h"
#include "../misc/skybox.h"

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

	std::shared_ptr<entity::Entity> entityById(unsigned int entityId);

	std::shared_ptr<light::Light> lightById(unsigned int lightId);

	void setSelectedObject(std::shared_ptr<Object> object);

	void setSelectedObject(unsigned int objectId);

	void setSkybox(std::shared_ptr<Skybox> skybox);

	void drawEntities();

	// draw selected entity and highlight around selected entity using stencil testing
	void drawSelectedEntity(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

	void drawSkybox(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

	std::shared_ptr<Object> selectedObject();

	std::vector<std::shared_ptr<collisions::Collidable>> collidableEntities();

	std::vector<std::shared_ptr<entity::Entity>> entityList();

	std::vector<std::shared_ptr<Object>> objectList();

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
	std::shared_ptr<Skybox> _skybox = nullptr;

	//selected entity
	std::shared_ptr<Object> _selectedObject = nullptr;
	shading::Color _selectedHighlightColor = shading::Color(252, 173, 3);
	float _selectedHighlightScaleFactor = 1.025f;
};