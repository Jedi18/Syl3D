#pragma once

#include <iostream>

namespace math
{
	class Vec2
	{
	public:
		Vec2();

		Vec2(float x, float y;

		float mag() const;

		Vec2 operator + (const Vec2& other) const;

		Vec2& operator += (const Vec2& other);

		Vec2 operator * (float k) const;

		Vec2& operator *= (float k);

		Vec2 operator - (const Vec2& other) const;

		static float dot(const Vec2& a, const Vec2& b);

		Vec2 normalized() const;

		void normalize();

		friend std::ostream& operator << (std::ostream& o, const Vec2& vec);

	public:
		float x;
		float y;
	};

	std::ostream& operator << (std::ostream& o, const Vec2& vec);
}