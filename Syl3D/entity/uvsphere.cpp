#include "uvsphere.h"

#include "../collisions/spherebb.h"

using namespace entity;

UVSphere::UVSphere(int parallels, int meridians, std::string shaderName)
	:
	Entity(shaderName),
	Collidable(new collisions::SphereBB(1)),
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

bool UVSphere::intersects(const math::Ray& ray) const {
	return _boundingBox->intersects(_pos, ray);
}

void UVSphere::scale(float factor) {
	Entity::scale(factor);
	dynamic_cast<collisions::SphereBB*>(_boundingBox)->scaleRadius(factor);
}

void UVSphere::accept(EntityVisitor& v) {
	v.visit(this);
}