#pragma once

#include "entity.h"
#include "../mesh/rectanglemesh.h"

namespace entity
{
	class Rectangle : public Entity
	{
	public:
		Rectangle();

		void draw() override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::RectangleMesh> _rectangle;
	};
}