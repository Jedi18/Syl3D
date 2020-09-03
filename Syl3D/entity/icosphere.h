#pragma once

#include "entity.h"
#include "../mesh/icospheremesh.h"

namespace entity
{
	class IcoSphere : public Entity
	{
	public:
		IcoSphere(int recursionLevel = 3);

		IcoSphere(math::Vec3 startingPos, int recursionLevel = 3);

		void draw() override;

	private:
		mesh::IcoSphereMesh _sphere;
	};
}
