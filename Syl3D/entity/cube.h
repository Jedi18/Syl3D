#pragma once

#include "entity.h"
#include "../mesh/cubemesh.h"

namespace entity
{
	class Cube : public Entity
	{
	public:
		Cube();

		void draw() override;

	private:
		mesh::CubeMesh _cube;
	};
}