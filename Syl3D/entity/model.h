#pragma once

#include "entity.h"

namespace entity
{
	class Model : public Entity
	{
	public:
		Model(std::string shaderName = "default");

		void draw() override;
	};
}