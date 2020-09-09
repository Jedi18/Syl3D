#include "icosphere.h"

using namespace entity;

IcoSphere::IcoSphere(int recursionLevel, std::string shaderName)
	:
	Entity(shaderName),
	_sphere(recursionLevel)
{
	this->initialize(&_sphere);
}

IcoSphere::IcoSphere(math::Vec3 startingPos, int recursionLevel, std::string shaderName)
	:
	IcoSphere(recursionLevel, shaderName)
{
	_pos = startingPos;
}

void IcoSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _sphere.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}