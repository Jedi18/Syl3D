#include "terrain.h"

using namespace entity;

Terrain::Terrain()
	:
	_terrain()
{
	this->initialize(&_terrain);
}

Terrain::Terrain(math::Vec3 startingPos)
	:
	Terrain()
{
	_pos = startingPos;
}

void Terrain::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _terrain.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}