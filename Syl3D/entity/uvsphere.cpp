#include "uvsphere.h"

using namespace entity;

UVSphere::UVSphere(int parallels, int meridians, std::string shaderName)
	:
	Entity(shaderName),
	_sphere(parallels, meridians)
{
	this->initialize(&_sphere);
}

UVSphere::UVSphere(math::Vec3 startingPos, int parallels, int meridians, std::string shaderName)
	:
	UVSphere(parallels, meridians, shaderName)
{
	_pos = startingPos;
}

void UVSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, _sphere.numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}