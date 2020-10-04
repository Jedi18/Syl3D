#pragma once

#include "entity.h"
#include "../mesh/uvspheremesh.h"

namespace entity
{
	class UVSphere : public Entity
	{
	public:
		UVSphere(int parallels = 10, int meridians = 10, std::string shaderName = "default");

		UVSphere(math::Vec3 startingPos, int parallels = 10, int meridians = 10, std::string shaderName = "default");

		void draw() override;

	private:
		std::shared_ptr<mesh::UVSphereMesh> _sphere;
	};
}