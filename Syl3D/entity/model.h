#pragma once

#include "entity.h"
#include "../mesh/modelmesh.h"

namespace entity
{
	class Model : public Entity
	{
	public:
		Model(const std::vector<mesh::ModelMesh>& meshes, std::string shaderName = "default");

		Model(std::string shaderName = "default");

		void draw() override;

	private:
		std::vector<mesh::ModelMesh> _meshes;
	};
}