#include "circle.h"

using namespace entity;

Circle::Circle()
	:
	_circle(std::make_shared<mesh::CircleMesh>())
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_circle) });
}

void Circle::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, _circle->numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}

void Circle::accept(EntityVisitor& v) {
	v.visit(this);
}