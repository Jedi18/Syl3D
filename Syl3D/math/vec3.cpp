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

Vec3 Vec3::operator + (const Vec3& other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3& Vec3::operator += (const Vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 Vec3::operator * (float k) const {
	return Vec3(x * k, y * k, z * k);
}

Vec3& Vec3::operator *= (float k) {
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

Vec3 Vec3::normalized() const {
	float m = mag();
	return Vec3(x / m, y / m, z / m);
}

void Vec3::normalize() {
	float m = mag();
	x = x / m;
	y = y / m;
	z = z / m;
}

std::ostream& math::operator << (std::ostream& o, const Vec3& vec) {
	o << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
	return o;
}

Vec3 Vec3::operator - (const Vec3& other) const {
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float Vec3::dot(const Vec3& a, const Vec3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}