#include "cube.h"

#include <math.h>

using namespace entity;

Cube::Cube(std::string shaderName)
	:
	Entity(shaderName),
	_cube(std::make_shared<mesh::CubeMesh>()),
	_boundingBox(_scale.x / 2)
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_cube) });
}

Cube::Cube(math::Vec3 startingPos) 
	:
	Cube()
{
	_pos = startingPos;
}

void Cube::draw() {
	if (!_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

bool Cube::intersects(const math::Ray& ray) const {
	return _boundingBox.intersects(_pos, ray);
}

void Cube::accept(EntityVisitor& v) {
	v.visit(this);
}