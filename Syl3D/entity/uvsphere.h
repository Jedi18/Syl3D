#pragma once

#include "entity.h"
#include "../mesh/uvspheremesh.h"

namespace entity
{
	class UVSphere : public Entity
	{
	public:
		UVSphere(int parallels = 10, int meridians = 10);

		UVSphere(math::Vec3 startingPos, int parallels = 10, int meridians = 10);

		void draw() override;

	private:
		mesh::UVSphereMesh _sphere;
	};
}