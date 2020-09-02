#include "cube.h"

using namespace entity;

Cube::Cube()
{
	this->initialize(&_cube);
}

Cube::Cube(math::Vec3 startingPos) 
	:
	Cube()
{
	_pos = startingPos;
}

void Cube::draw() {
	if (!_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}