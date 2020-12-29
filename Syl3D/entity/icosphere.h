#pragma once

#include "entity.h"
#include "../mesh/icospheremesh.h"
#include "../collisions/collidable.h"

namespace entity
{
	class IcoSphere : public Entity, public collisions::Collidable
	{
	public:
		IcoSphere(int recursionLevel = 3, std::string shaderName = "default");

		IcoSphere(math::Vec3 startingPos, int recursionLevel = 3, std::string shaderName = "default");

		void draw() override;

		bool intersects(const math::Ray& ray) const override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::IcoSphereMesh> _sphere;
	};
}
