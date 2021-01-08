#include "terrain.h"

using namespace entity;

Terrain::Terrain(utility::HeightmapData& heightmapData)
	:
	Entity(),
	_terrain(std::make_shared<mesh::TerrainMesh>(heightmapData))
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_terrain) });
}

Terrain::Terrain(math::Vec3 startingPos, utility::HeightmapData& heightmapData)
	:
	Terrain(heightmapData)
{
	_pos = startingPos;
}

void Terrain::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, _terrain->numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}

void Terrain::accept(EntityVisitor& v) {
	v.visit(this);
}