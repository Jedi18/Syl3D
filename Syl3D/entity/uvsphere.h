#pragma once

#include "entity.h"
#include "../collisions/collidable.h"
#include "../mesh/uvspheremesh.h"

namespace entity
{
	class UVSphere : public Entity, public collisions::Collidable
	{
	public:
		UVSphere(int parallels = 10, int meridians = 10);

		UVSphere(math::Vec3 startingPos, int parallels = 10, int meridians = 10);

		void draw() override;

		bool intersects(const math::Ray& ray) const override;

		void scale(float factor) override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::UVSphereMesh> _sphere;
	};
}