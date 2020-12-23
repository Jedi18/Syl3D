#pragma once

#include "entity.h"
#include "../mesh/icospheremesh.h"

namespace entity
{
	class IcoSphere : public Entity
	{
	public:
		IcoSphere(int recursionLevel = 3, std::string shaderName = "default");

		IcoSphere(math::Vec3 startingPos, int recursionLevel = 3, std::string shaderName = "default");

		void draw() override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::IcoSphereMesh> _sphere;
	};
}
