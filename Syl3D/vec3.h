#pragma once

namespace math
{
	class Vec3
	{
	public:
		Vec3();

		Vec3(float x, float y, float z);

		float mag() const;

	public:
		float x;
		float y;
		float z;
	};
}