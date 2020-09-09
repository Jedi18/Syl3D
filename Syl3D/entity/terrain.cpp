#include "terrain.h"

using namespace entity;

Terrain::Terrain(utility::HeightmapData& heightmapData, std::string shaderName)
	:
	Entity(shaderName),
	_terrain(heightmapData)
{
	this->initialize(&_terrain);
}

Terrain::Terrain(math::Vec3 startingPos, utility::HeightmapData& heightmapData, std::string shaderName)
	:
	Terrain(heightmapData, shaderName)
{
	_pos = startingPos;
}

void Terrain::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _terrain.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}