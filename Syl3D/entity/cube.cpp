#include "cube.h"

using namespace entity;

Cube::Cube()
{
	this->initialize(&_cube);
}

void Cube::draw() {
	if (!_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}