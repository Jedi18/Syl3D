#pragma once

#include "entity.h"
#include "../mesh/terrainmesh.h"

namespace entity
{
	class Terrain : public Entity
	{
	public:
		Terrain(utility::HeightmapData& heightmapData);

		Terrain(math::Vec3 startingPos, utility::HeightmapData& heightmapData);

		void draw() override;

		void accept(EntityVisitor& v) override;

	private:
		std::shared_ptr<mesh::TerrainMesh> _terrain;
	};
}