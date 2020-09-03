#include "uvsphere.h"

using namespace entity;

UVSphere::UVSphere()
{
	this->initialize(&_sphere);
}

UVSphere::UVSphere(math::Vec3 startingPos)
	:
	UVSphere()
{
	_pos = startingPos;
}

void UVSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _sphere.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}