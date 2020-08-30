#include "vec3.h"
#include <cmath>

using namespace math;

Vec3::Vec3() 
	:
	x(0), y(0), z(0)
{}

Vec3::Vec3(float x, float y, float z)
	:
	x(x), y(y), z(z)
{}

float Vec3::mag() const {
	return std::sqrt(x * x + y * y + z * z);
}