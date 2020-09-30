#pragma once

#include "entity.h"
#include "../mesh/cubemesh.h"
#include "../collisions/SphereBB.h"

namespace entity
{
	class Cube : public Entity
	{
	public:
		Cube(std::string shaderName = "default");

		Cube(math::Vec3 startingPos);

		void draw() override;

		bool intersects(const math::Ray& ray) const;

	private:
		mesh::CubeMesh _cube;
		collisions::SphereBB _boundingBox;
	};
}