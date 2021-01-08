#pragma once

#include "entity.h"
#include "../mesh/modelmesh.h"

namespace entity
{
	class Model : public Entity
	{
	public:
		Model(const std::vector<std::shared_ptr<mesh::ModelMesh>>& meshes);

		void draw() override;

		void accept(EntityVisitor& v) override;

	private:
		std::vector<std::shared_ptr<mesh::ModelMesh>> _meshes;
	};
}