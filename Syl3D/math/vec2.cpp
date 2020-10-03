#include "vec2.h"
#include <cmath>

using namespace math;

Vec2::Vec2()
	:
	x(0), y(0)
{}

Vec2::Vec2(float x, float y)
	:
	x(x), y(y)
{}

float Vec2::mag() const {
	return std::sqrt(x * x + y * y);
}

Vec2 Vec2::operator + (const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2& Vec2::operator += (const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 Vec2::operator * (float k) const {
	return Vec2(x * k, y * k);
}

Vec2& Vec2::operator *= (float k) {
	x *= k;
	y *= k;
	return *this;
}

Vec2 Vec2::normalized() const {
	float m = mag();
	return Vec2(x / m, y / m);
}

void Vec2::normalize() {
	float m = mag();
	x = x / m;
	y = y / m;
}

std::ostream& math::operator << (std::ostream& o, const Vec2& vec) {
	o << "(" << vec.x << "," << vec.y << ")";
	return o;
}

Vec2 Vec2::operator - (const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

float Vec2::dot(const Vec2& a, const Vec2& b) {
	return (a.x * b.x) + (a.y * b.y);
}