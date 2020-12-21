#include "rectangle.h"

using namespace entity;

Rectangle::Rectangle()
	:
	_rectangle(std::make_shared<mesh::RectangleMesh>())
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_rectangle) });
}

void Rectangle::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Rectangle::accept(EntityVisitor& v) {
	v.visit(this);
}