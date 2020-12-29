#pragma once

#include "entity.h"
#include "entitycontainer.h"

class EntityFactory
{
public:
	enum class EntityType {
		Cube,
		UVSphere,
		IcoSphere
	};

	static EntityFactory* entityFactory();

	void setEntityContainer(std::shared_ptr<EntityContainer> entityContainer);

	std::shared_ptr<EntityContainer> entityContainer();

	static void releaseInstance();

	std::shared_ptr<entity::Entity> addEntity(const EntityType entityType);

	static unsigned int generateID();

public:
	static std::map<EntityType, std::string> ENTITY_NAMES;

private:
	EntityFactory();

private:
	static EntityFactory* _instance;
	static unsigned int ENTITY_COUNT;
	static std::map<int, std::string> _defaultShaders;

	std::shared_ptr<EntityContainer> _entityContainer = nullptr;
};

