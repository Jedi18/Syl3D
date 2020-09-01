#include "triangle.h"

using namespace entity;

Triangle::Triangle()
{
	this->initialize(&_triangle);
}

void Triangle::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}