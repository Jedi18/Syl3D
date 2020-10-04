#include "triangle.h"

using namespace entity;

Triangle::Triangle()
	:
	_triangle(std::make_shared<mesh::TriangleMesh>())
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_triangle) });
}

void Triangle::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}