#pragma once

#include "entity.h"
#include "../mesh/terrainmesh.h"

namespace entity
{
	class Terrain : public Entity
	{
	public:
		Terrain(utility::HeightmapData& heightmapData, std::string shaderName = "default");

		Terrain(math::Vec3 startingPos, utility::HeightmapData& heightmapData, std::string shaderName = "default");

		void draw() override;

	private:
		mesh::TerrainMesh _terrain;
	};
}