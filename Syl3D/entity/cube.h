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

	private:
		mesh::CubeMesh _cube;
	};
}