#pragma once

#include "entity.h"
#include "../mesh/circlemesh.h"

namespace entity
{
	class Circle : public Entity
	{
	public:
		Circle();

		void draw() override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::CircleMesh> _circle;
	};
}