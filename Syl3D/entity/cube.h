#pragma once

#include "entity.h"
#include "../mesh/cubemesh.h"
#include "../collisions/SphereBB.h"
#include "../collisions/Collidable.h"

namespace entity
{
	class Cube : public Entity, public collisions::Collidable
	{
	public:
		Cube();

		Cube(math::Vec3 startingPos);

		void draw() override;

		bool intersects(const math::Ray& ray) const override;

		void accept(EntityVisitor& v) override;

		void scale(float factor) override;

	private:
		std::shared_ptr<mesh::CubeMesh> _cube;
	};
}