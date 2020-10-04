#pragma once

#include "entity.h"
#include "../mesh/modelmesh.h"

namespace entity
{
	class Model : public Entity
	{
	public:
		Model(const std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes, std::string shaderName = "default");

		void draw() override;

	private:
		std::vector<std::shared_ptr<mesh::ModelMesh>> _meshes;
	};
}