#pragma once

#include "entity.h"
#include "../lights/light.h"
#include "entitycontainer.h"

class EntityFactory
{
public:
	enum class EntityType {
		Cube,
		UVSphere,
		IcoSphere
	};

	enum class LightType {
		Point,
		Directional,
		Spot
	};

	static EntityFactory* entityFactory();

	void setEntityContainer(std::shared_ptr<EntityContainer> entityContainer);

	std::shared_ptr<EntityContainer> entityContainer();

	static void releaseInstance();

	std::shared_ptr<entity::Entity> addEntity(const EntityType entityType);

	std::shared_ptr<light::Light> addLight(const LightType lightType);

	static unsigned int generateID();

public:
	static std::map<EntityType, std::string> ENTITY_NAMES;
	static std::map<LightType, std::string> LIGHT_NAMES;

private:
	EntityFactory();

private:
	static EntityFactory* _instance;
	static unsigned int ENTITY_COUNT;

	std::shared_ptr<EntityContainer> _entityContainer = nullptr;
};

