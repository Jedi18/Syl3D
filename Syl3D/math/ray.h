#pragma once

#include "vec3.h"

namespace math
{
	class Ray
	{
	public:
		Ray();

		Ray(math::Vec3 o, math::Vec3 dir);

	public:
		const math::Vec3 origin;
		const math::Vec3 direction;
	};
}