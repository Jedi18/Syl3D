#include "icosphere.h"

using namespace entity;

IcoSphere::IcoSphere(int recursionLevel)
	:
	_sphere(recursionLevel)
{
	this->initialize(&_sphere);
}

IcoSphere::IcoSphere(math::Vec3 startingPos, int recursionLevel)
	:
	IcoSphere(recursionLevel)
{
	_pos = startingPos;
}

void IcoSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _sphere.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}