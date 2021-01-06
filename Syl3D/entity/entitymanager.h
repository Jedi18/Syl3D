#pragma once

#include "entity.h"
#include "../texture/texturematerial.h"

namespace entity
{
	/**
	* To do operations safely that require changing multiple class values
	*/
	class EntityManager
	{
	public:
		static EntityManager* entityManager();

		static void releaseInstance();

		void changeTexture(std::shared_ptr<entity::Entity> entity, std::shared_ptr<TextureMaterial> newTextureMaterial) const;

	private:
		EntityManager();

	private:
		static EntityManager* _instance;
	};
}

