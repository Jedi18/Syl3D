#include "cube.h"

#include <math.h>

using namespace entity;

Cube::Cube()
	:
	Entity(),
	Collidable(new collisions::SphereBB(_scale.x/2)),
	_cube(std::make_shared<mesh::CubeMesh>())
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
	return _boundingBox->intersects(_pos, ray);
}

void Cube::scale(float factor) {
	Entity::scale(factor);
	dynamic_cast<collisions::SphereBB*>(_boundingBox)->scaleRadius(factor);
}

void Cube::accept(EntityVisitor& v) {
	v.visit(this);
}