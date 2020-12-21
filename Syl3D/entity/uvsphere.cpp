#include "uvsphere.h"

using namespace entity;

UVSphere::UVSphere(int parallels, int meridians, std::string shaderName)
	:
	Entity(shaderName),
	_sphere(std::make_shared<mesh::UVSphereMesh>(parallels, meridians))
{
	this->initialize({ std::static_pointer_cast<mesh::Mesh>(_sphere) });
}

UVSphere::UVSphere(math::Vec3 startingPos, int parallels, int meridians, std::string shaderName)
	:
	UVSphere(parallels, meridians, shaderName)
{
	_pos = startingPos;
}

void UVSphere::draw() {
	if (_usesEBO) {
		glBindVertexArray(_VAOs[0]);
		glDrawElements(GL_TRIANGLES, _sphere->numIndices() / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}
}

void UVSphere::accept(EntityVisitor& v) {
	v.visit(this);
}