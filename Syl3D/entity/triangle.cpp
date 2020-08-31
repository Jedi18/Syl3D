#include "triangle.h"

using namespace entity;

Triangle::Triangle()
{
	this->initialize(&_triangle);
}

void Triangle::draw() {
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}