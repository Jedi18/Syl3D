#pragma once

#include "entity.h"
#include "../mesh/cubemesh.h"

namespace entity
{
	class Cube : public Entity
	{
	public:
		Cube(std::string shaderName = "default");

		Cube(math::Vec3 startingPos);

		void draw() override;

		bool intersects(math::Vec3 raycenter, math::Vec3 raydirection);

	private:
		mesh::CubeMesh _cube;
	};
}