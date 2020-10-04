#pragma once

#include "entity.h"
#include "../mesh/trianglemesh.h"

namespace entity
{
	class Triangle : public Entity 
	{
	public:
		Triangle();

		void draw() override;

	private:
		std::shared_ptr<mesh::TriangleMesh> _triangle;
	};
}