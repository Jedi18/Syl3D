#pragma once

#include "entity.h"
#include "../mesh/terrainmesh.h"

namespace entity
{
	class Terrain : public Entity
	{
	public:
		Terrain();

		Terrain(math::Vec3 startingPos);

		void draw() override;

	private:
		mesh::TerrainMesh _terrain;
	};
}