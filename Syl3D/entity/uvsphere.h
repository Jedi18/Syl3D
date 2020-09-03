#pragma once

#include "entity.h"
#include "../mesh/uvspheremesh.h"

namespace entity
{
	class UVSphere : public Entity
	{
	public:
		UVSphere();

		UVSphere(math::Vec3 startingPos);

		void draw() override;

	private:
		mesh::UVSphereMesh _sphere;
	};
}