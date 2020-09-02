#pragma once

namespace math
{
	class Vec3
	{
	public:
		Vec3();

		Vec3(float x, float y, float z);

		float mag() const;

		Vec3 operator + (const Vec3& other);

		Vec3& operator += (const Vec3& other);

		Vec3 operator * (float k);

		Vec3& operator *= (float k);

	public:
		float x;
		float y;
		float z;
	};
}