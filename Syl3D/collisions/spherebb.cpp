#include "spherebb.h"

using namespace collisions;

SphereBB::SphereBB(float r) 
	:
	radius(r)
{}

void SphereBB::setRadius(float rad) {
	radius = rad;
}

bool SphereBB::intersects(const math::Vec3& boundingBoxCenter, const math::Ray& ray) const {
	math::Vec3 oc = ray.origin - boundingBoxCenter;
	float b = math::Vec3::dot(oc, ray.direction);
	float c = math::Vec3::dot(oc, oc) - (radius * radius);

	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float determinant = b * b - c;
	if (determinant < 0) {
		return false;
	}

	return true;
}