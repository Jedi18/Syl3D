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

	private:
		mesh::RectangleMesh _rectangle;
	};
}