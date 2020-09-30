#include "cube.h"

#include <math.h>

using namespace entity;

Cube::Cube(std::string shaderName)
	:
	Entity(shaderName)
{
	this->initialize(&_cube);
}

Cube::Cube(math::Vec3 startingPos) 
	:
	Cube()
{
	_pos = startingPos;
}

void Cube::draw() {
	if (!_usesEBO) {
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

bool Cube::intersects(math::Vec3 raycenter, math::Vec3 raydirection) {
	float r = _scale.x / 2;
	math::Vec3 oc = raycenter - _pos;
	float b = math::Vec3::dot(oc, raydirection);
	float c = math::Vec3::dot(oc, oc) - (r * r);

	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float determinant = b * b - c;

	if (determinant < 0) {
		return false;
	}

	//float rootd = std::sqrtf(determinant);
	//float t1 = -b + rootd;
	//float t2 = -b - rootd;

	return true;
}