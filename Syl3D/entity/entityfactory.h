#pragma once

#include "entity.h"
#include "entitycontainer.h"

class EntityFactory
{
public:
	enum class EntityType {
		Cube,
		Terrain
	};

	static EntityFactory* entityFactory();

	static void setEntityContainer(std::shared_ptr<EntityContainer> entityContainer);

	static void releaseInstance();

	std::shared_ptr<entity::Entity> addEntity(const EntityType entityType);

private:
	static EntityFactory* _instance;
	static unsigned int ENTITY_COUNT;
	static std::shared_ptr<EntityContainer> _entityContainer;
};

